#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel {

	static bool s_GLFWInitialized = false;

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

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
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