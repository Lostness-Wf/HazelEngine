#pragma once

//Windows窗口类

#include "Hazel/Window.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	/*WindowsWindow 的类，它继承自 Window 类。WindowsWindow 类实现了 Window 类中定义的纯虚函数，
	OnUpdate、GetWidth、GetHeight、SetEventCallback、SetVSync 和 IsVSync。
	此外，它还包含两个私有虚函数：Init 和 Shutdown，用于初始化和关闭窗，
	它还包含一个名为 WindowData 的结构体，用于存储窗口的相关数据，
	如标题、宽度、高度、垂直同步状态和事件回调函数。*/
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

		/*WindowData 的结构体，用于存储窗口的相关数据，
		标题、宽度、高度、垂直同步状态和事件回调函数。*/
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