#include "hzpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		//HZ_CORE_ASSERT(windowHandle, "Window handle is null!")
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
		HZ_CORE_INFO("  Vendor: {0}", (const void*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", (const void*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", (const void*)glGetString(GL_VERSION));

		HZ_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		HZ_PROFILE_FUNCTION();

		//glfwSwapBuffers �������ڽ���ָ�����ڵ�ǰ�󻺳���������ζ�����Ὣ�󻺳����е�ͼ����ʾ����Ļ�ϣ�
		//Ȼ��ǰ��������Ϊ�󻺳�������������һ֡�л���ͼ��
		glfwSwapBuffers(m_WindowHandle);
	}

}