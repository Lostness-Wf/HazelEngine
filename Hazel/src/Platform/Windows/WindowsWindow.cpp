#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Hazel {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	/*Init �������ڳ�ʼ�����ڡ������ȼ�� s_GLFWInitialized �����Ƿ�Ϊ false������ǣ�
	����� glfwInit ������ʼ�� GLFW �⣬���� s_GLFWInitialized ��Ϊ true��
	Ȼ����ʹ�� glfwCreateWindow ��������һ�� GLFW ���ڣ�
	��ʹ�� glfwMakeContextCurrent �������ô��ڵ� OpenGL ����������Ϊ��ǰ�̵߳������ġ�
	��������� SetVSync �������ô�ֱͬ����*/
	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		//��ʼ��GLAD��gladLoadGLLoader����һ��GLADloadproc���͵Ĳ�����glfwGetProcAddress����OpenGL����ָ��
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		/*glfwSetWindowSizeCallback����Ϊm_Window������һ�����ڴ�С�ص�������
		�����ڴ�С�����仯ʱ�������ô˻ص��������ص�������һ��lambda���ʽ��
		����������������һ��ָ��GLFWwindow��ָ��������������ֱ��ʾ���ڵ��¿�Ⱥ͸߶ȡ�
		��lambda���ʽ�ĺ������У�����ͨ������glfwGetWindowUserPointer��������ȡָ��WindowData��ָ�룬
		����������Ϊdata��Ȼ�󣬸���data�еĿ�Ⱥ͸߶�ֵ��������������һ��WindowResizeEvent����
		��ʹ���µĿ�Ⱥ͸߶ȳ�ʼ��������󣬵���data.EventCallback�����¼�������Ϊ�������ݡ�*/
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}


	/*glfwPollEvents()�������ڴ�����ϵͳ�е��¼��������鴰��ϵͳ���Ƿ���δ������¼���
	����������롢����ƶ��򴰿ڴ�С�ı�ȡ������δ������¼���
	���������Ӧ���¼��ص�������������Щ�¼���
	glfwSwapBuffers(m_Window) �������ڽ������ڵ�ǰ�󻺳������� OpenGL �У�
	��Ⱦ����ͨ�����ں�̨�������н��еģ��Ա��⻭��˺�Ѻ���˸������Ⱦ��ɺ�
	����Ҫ���� glfwSwapBuffers ����������ǰ�󻺳���������Ⱦ�����ʾ����Ļ��*/
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}