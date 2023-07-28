#include "hzpch.h"
#include "Application.h"

#include "Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Hazel {

	/*使用std::bind将成员函数Application::x绑定到this指针，并将第一个参数绑定到占位符std::placeholders::_1。
	这意味着当调用生成的函数对象时，第一个参数将替换占位符_1。std::bind是一个函数模板，
	它返回一个可调用对象，该对象将给定的参数绑定到给定的函数或可调用对象。
	占位符用于指定哪些参数不应绑定，而应在调用生成的函数对象时提供。*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Hazel::Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		/*调用了m_Window的SetEventCallback方法，并将其参数设置为BIND_EVENT_FN(OnEvent)的结果。
		由于BIND_EVENT_FN是一个宏，它将被展开为std::bind(&Application::OnEvent, this, std::placeholders::_1)。
		这意味着，SetEventCallback方法的参数将是一个可调用对象，该对象绑定到成员函数Application::OnEvent，
		并将第一个参数绑定到占位符std::placeholders::_1。当调用生成的函数对象时，第一个参数将替换占位符_1。*/
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		//test111
		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Hazel::Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		/*从 m_LayerStack 的末尾开始遍历，直到到达 m_LayerStack 的开头。每次迭代中，
		调用当前图层的 OnEvent 函数，并将事件 e 作为参数传递给它。如果事件 e 被处理（即 e.Handled 为 true），
		则循环会提前结束，不再继续遍历剩余的图层。目的是将事件 e 传递给图层栈中的每个图层，
		直到事件被处理或所有图层都被遍历完毕。*/
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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//glfw test
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//input polling test
			auto [x, y] = Input::GetMousePosition();
			HZ_CORE_TRACE("{0}, {1}", x, y);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}