#include "hzpch.h"
#include "Application.h"

#include "Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Hazel {

	/*ʹ��std::bind����Ա����Application::x�󶨵�thisָ�룬������һ�������󶨵�ռλ��std::placeholders::_1��
	����ζ�ŵ��������ɵĺ�������ʱ����һ���������滻ռλ��_1��std::bind��һ������ģ�壬
	������һ���ɵ��ö��󣬸ö��󽫸����Ĳ����󶨵������ĺ�����ɵ��ö���
	ռλ������ָ����Щ������Ӧ�󶨣���Ӧ�ڵ������ɵĺ�������ʱ�ṩ��*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Hazel::Application::Application()
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

		//test triangle
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		//test shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Hazel::Application::~Application()
	{

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
			//window color
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			//test shader
			m_Shader->Bind();

			//test triangle
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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