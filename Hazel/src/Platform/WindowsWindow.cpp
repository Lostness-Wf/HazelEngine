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

	/*Init 函数用于初始化窗口。它首先检查 s_GLFWInitialized 变量是否为 false，如果是，
	则调用 glfwInit 函数初始化 GLFW 库，并将 s_GLFWInitialized 设为 true。
	然后，它使用 glfwCreateWindow 函数创建一个 GLFW 窗口，
	并使用 glfwMakeContextCurrent 函数将该窗口的 OpenGL 上下文设置为当前线程的上下文。
	最后，它调用 SetVSync 函数启用垂直同步。*/
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


	/*glfwPollEvents()函数用于处理窗口系统中的事件。它会检查窗口系统中是否有未处理的事件，
	例如键盘输入、鼠标移动或窗口大小改变等。如果有未处理的事件，
	它会调用相应的事件回调函数来处理这些事件。
	glfwSwapBuffers(m_Window) 函数用于交换窗口的前后缓冲区。在 OpenGL 中，
	渲染操作通常是在后台缓冲区中进行的，以避免画面撕裂和闪烁。当渲染完成后，
	你需要调用 glfwSwapBuffers 函数来交换前后缓冲区，将渲染结果显示在屏幕上*/
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