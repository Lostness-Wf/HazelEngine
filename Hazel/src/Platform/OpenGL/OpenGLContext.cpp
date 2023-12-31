#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		//初始化GLAD，gladLoadGLLoader接受一个GLADloadproc类型的参数，glfwGetProcAddress返回OpenGL函数指针
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		//GPU Version
		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		/*glfwSwapBuffers 函数用于交换指定窗口的前后缓冲区。这意味着它会将后缓冲区中的图像显示到屏幕上，
		然后前缓冲区成为后缓冲区，用于在下一帧中绘制图像。*/
		glfwSwapBuffers(m_WindowHandle);
	}

}