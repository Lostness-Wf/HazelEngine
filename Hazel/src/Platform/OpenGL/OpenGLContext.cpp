#include "hzpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		HZ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);

		//��ʼ��GLAD��gladLoadGLLoader����һ��GLADloadproc���͵Ĳ�����glfwGetProcAddress����OpenGL����ָ��
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
		HZ_PROFILE_FUNCTION();

		/*glfwSwapBuffers �������ڽ���ָ�����ڵ�ǰ�󻺳���������ζ�����Ὣ�󻺳����е�ͼ����ʾ����Ļ�ϣ�
		Ȼ��ǰ��������Ϊ�󻺳�������������һ֡�л���ͼ��*/
		glfwSwapBuffers(m_WindowHandle);
	}

}