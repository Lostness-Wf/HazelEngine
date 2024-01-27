#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	/*成员函数分为静态成员函数和虚成员函数两种。静态成员函数提供了一个公共接口，供外部调用者使用，
	而虚成员函数则用于在派生类中实现具体的功能。这种设计模式被称为“非虚接口”（Non - Virtual Interface，NVI），
	它的目的是将接口与实现分离，使得接口更加稳定，便于维护和扩展。在这种设计模式中，静态成员函数充当了接口的角色，
	它们定义了类所能提供的操作。虚成员函数则充当了实现的角色，它们在派生类中被重写，以实现具体的功能。
	这种设计模式的优点在于，它将接口与实现分离，使得接口更加稳定，便于维护和扩展。当需要修改或扩展类的功能时，
	只需在派生类中重写虚成员函数即可，而无需修改静态成员函数的接口。*/
	class HAZEL_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};

}