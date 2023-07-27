#pragma once

#include "hzpch.h"
#include "Hazel\Core.h"

namespace Hazel {

	//�¼�ϵͳ���ڻ��赲���̣������¼�ʱ��ֹͣapp���̣������¼�

	//�����¼�
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//�¼���𣬿�����������ĳ�����¼�
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

	//##��ǰ������Ϊһ���Ǻţ�����֮�����һ���ո�
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//Event����
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

	//EventDispatcher���ڸ��ݴ�����¼��Զ���������
	class EventDispatcher
	{
		/*������һ��ģ�庯�� Dispatch��������һ�� EventFn<T> ���͵ĺ���������Ϊ������
		Dispatch �������ȼ���¼������Ƿ���ģ����� T ƥ�䣬���ƥ�䣬����ô���ĺ������� func �������¼���
		�����¼��� m_Handled ��Ա����Ϊ func �ķ���ֵ���������¼�����ƥ�䣬Dispatch �������� true�����򷵻� false*/
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
