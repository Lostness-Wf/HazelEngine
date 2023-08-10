#pragma once

#include "Core.h"

#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/ImGui/ImGuiLayer.h"

namespace Hazel {

	class Application
	{
	public:
		Application();
		/*在 C++11 中，当一个函数后面加上 = default 时，表示这个函数是一个默认函数。编译器将为显式声明的默认函数自动生成函数体。
		编译器自动生成的默认函数通常比手动定义的函数具有更高的执行效率。
		此外，使用 =default 可以清楚地表明您希望使用编译器生成的默认行为，这有助于提高代码的可读性。*/
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		
	private:
		static Application* s_Instance;
	};

	//TODO:difine in sandbox
	Application* CreateApplication();
}

