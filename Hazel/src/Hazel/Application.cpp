#include "hzpch.h"
#include "Application.h"

#include "Log.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	/*ʹ��std::bind����Ա����Application::x�󶨵�thisָ�룬������һ�������󶨵�ռλ��std::placeholders::_1��
	����ζ�ŵ��������ɵĺ�������ʱ����һ���������滻ռλ��_1��std::bind��һ������ģ�壬
	������һ���ɵ��ö��󣬸ö��󽫸����Ĳ����󶨵������ĺ�����ɵ��ö���
	ռλ������ָ����Щ������Ӧ�󶨣���Ӧ�ڵ������ɵĺ�������ʱ�ṩ��*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Hazel::Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());

		/*������m_Window��SetEventCallback�������������������ΪBIND_EVENT_FN(OnEvent)�Ľ����
		����BIND_EVENT_FN��һ���꣬������չ��Ϊstd::bind(&Application::OnEvent, this, std::placeholders::_1)��
		����ζ�ţ�SetEventCallback�����Ĳ�������һ���ɵ��ö��󣬸ö���󶨵���Ա����Application::OnEvent��
		������һ�������󶨵�ռλ��std::placeholders::_1�����������ɵĺ�������ʱ����һ���������滻ռλ��_1��*/
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Hazel::Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//test
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}