#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {

	/*��Ա������Ϊ��̬��Ա���������Ա�������֡���̬��Ա�����ṩ��һ�������ӿڣ����ⲿ������ʹ�ã�
	�����Ա��������������������ʵ�־���Ĺ��ܡ��������ģʽ����Ϊ������ӿڡ���Non - Virtual Interface��NVI����
	����Ŀ���ǽ��ӿ���ʵ�ַ��룬ʹ�ýӿڸ����ȶ�������ά������չ�����������ģʽ�У���̬��Ա�����䵱�˽ӿڵĽ�ɫ��
	���Ƕ������������ṩ�Ĳ��������Ա������䵱��ʵ�ֵĽ�ɫ���������������б���д����ʵ�־���Ĺ��ܡ�
	�������ģʽ���ŵ����ڣ������ӿ���ʵ�ַ��룬ʹ�ýӿڸ����ȶ�������ά������չ������Ҫ�޸Ļ���չ��Ĺ���ʱ��
	ֻ��������������д���Ա�������ɣ��������޸ľ�̬��Ա�����Ľӿڡ�*/
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