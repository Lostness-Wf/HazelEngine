#include "hzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Hazel/Application.h"

namespace Hazel {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		/*ImGui::GetIO() 函数返回一个指向 ImGuiIO 结构体的引用，该结构体包含了 ImGui 的输入 / 输出设置。
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors 表示后端支持鼠标光标，
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos 则表示后端支持设置鼠标位置。*/
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		//返回一个指向ImGuiIO结构体的引用，该结构体包含了ImGui的输入 / 输出设置
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		//io.DisplaySize 变量用于设置ImGui的显示大小，这里将其设置为应用程序窗口的大小
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		//返回从 GLFW 初始化以来经过的秒数
		float time = (float)glfwGetTime();
		//io.DeltaTime变量用于设置ImGui的帧时间，即两帧之间的时间间隔。
		//这里将其设置为当前时间减去上一帧的时间，如果上一帧的时间为 0，则将其设置为 1 / 60 秒。
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		//准备OpenGL3后端
		ImGui_ImplOpenGL3_NewFrame();
		//ImGui的新帧
		ImGui::NewFrame();

		static bool show = true;
		//显示一个包含ImGui 所有功能演示的窗口，其中 show 变量控制窗口的显示状态。
		ImGui::ShowDemoWindow(&show);

		//调用ImGui::Render()生成绘制数据
		ImGui::Render();
		//将ImGui生成的绘制数据传递给OpenGL3后端进行渲染。
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

	}

}