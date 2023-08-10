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
		/*�� C++11 �У���һ������������� = default ʱ����ʾ���������һ��Ĭ�Ϻ�������������Ϊ��ʽ������Ĭ�Ϻ����Զ����ɺ����塣
		�������Զ����ɵ�Ĭ�Ϻ���ͨ�����ֶ�����ĺ������и��ߵ�ִ��Ч�ʡ�
		���⣬ʹ�� =default ��������ر�����ϣ��ʹ�ñ��������ɵ�Ĭ����Ϊ������������ߴ���Ŀɶ��ԡ�*/
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

