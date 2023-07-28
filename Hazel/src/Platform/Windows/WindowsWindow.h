#pragma once

//Windows������

#include "Hazel/Window.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	/*WindowsWindow ���࣬���̳��� Window �ࡣWindowsWindow ��ʵ���� Window ���ж���Ĵ��麯����
	OnUpdate��GetWidth��GetHeight��SetEventCallback��SetVSync �� IsVSync��
	���⣬������������˽���麯����Init �� Shutdown�����ڳ�ʼ���͹رմ���
	��������һ����Ϊ WindowData �Ľṹ�壬���ڴ洢���ڵ�������ݣ�
	����⡢��ȡ��߶ȡ���ֱͬ��״̬���¼��ص�������*/
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		/*WindowData �Ľṹ�壬���ڴ洢���ڵ�������ݣ�
		���⡢��ȡ��߶ȡ���ֱͬ��״̬���¼��ص�������*/
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}