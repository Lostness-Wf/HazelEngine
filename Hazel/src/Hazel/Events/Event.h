#pragma once

#include "hzpch.h"
#include "Hazel\Core.h"

namespace Hazel {

	//事件系统现在会阻挡进程，发生事件时会停止app进程，处理事件

	//各种事件
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//事件类别，可以用来过滤某几种事件
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

	//##将前后连接为一个记号，否则之间会有一个空格
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//Event基类
	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	//EventDispatcher用于根据传入的事件自动分配类型
	class EventDispatcher
	{
		/*定义了一个模板函数 Dispatch，它接受一个 EventFn<T> 类型的函数对象作为参数。
		Dispatch 函数首先检查事件类型是否与模板参数 T 匹配，如果匹配，则调用传入的函数对象 func 来处理事件，
		并将事件的 m_Handled 成员设置为 func 的返回值。最后，如果事件类型匹配，Dispatch 函数返回 true，否则返回 false*/
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
