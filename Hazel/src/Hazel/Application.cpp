#include "hzpch.h"
#include "Application.h"

#include "Log.h"

#include "Hazel/Renderer/Renderer.h"

#include "Input.h"
#include "GLFW/glfw3.h"

namespace Hazel {

	/*ʹ��std::bind����Ա����Application::x�󶨵�thisָ�룬������һ�������󶨵�ռλ��std::placeholders::_1��
	����ζ�ŵ��������ɵĺ�������ʱ����һ���������滻ռλ��_1��std::bind��һ������ģ�壬
	������һ���ɵ��ö��󣬸ö��󽫸����Ĳ����󶨵������ĺ�����ɵ��ö���
	ռλ������ָ����Щ������Ӧ�󶨣���Ӧ�ڵ������ɵĺ�������ʱ�ṩ��*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		/*������m_Window��SetEventCallback�������������������ΪBIND_EVENT_FN(OnEvent)�Ľ����
		����BIND_EVENT_FN��һ���꣬������չ��Ϊstd::bind(&Application::OnEvent, this, std::placeholders::_1)��
		����ζ�ţ�SetEventCallback�����Ĳ�������һ���ɵ��ö��󣬸ö���󶨵���Ա����Application::OnEvent��
		������һ�������󶨵�ռλ��std::placeholders::_1�����������ɵĺ�������ʱ����һ���������滻ռλ��_1��*/
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		/*�� m_LayerStack ��ĩβ��ʼ������ֱ������ m_LayerStack �Ŀ�ͷ��ÿ�ε����У�
		���õ�ǰͼ��� OnEvent �����������¼� e ��Ϊ�������ݸ���������¼� e �������� e.Handled Ϊ true����
		��ѭ������ǰ���������ټ�������ʣ���ͼ�㡣Ŀ���ǽ��¼� e ���ݸ�ͼ��ջ�е�ÿ��ͼ�㣬
		ֱ���¼������������ͼ�㶼��������ϡ�*/
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//��ȡ֡ʱ��
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}