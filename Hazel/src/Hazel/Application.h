#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Window.h"
#include "LayerStack.h"

#include "Hazel/Renderer/OrthographicCamera.h"

namespace Hazel {

	class HAZEL_API Application
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

		//test triangle
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		//test square
		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	//TODO:difine in sandbox
	Application* CreateApplication();
}

