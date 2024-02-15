#pragma once

#include <string>

namespace Hazel {

	class FileDialogs
	{
	public:
		//std::optional<> ��һ�� C++17 ��������������ͣ������԰���һ������Ϊ std::string �Ķ�����߲������κζ���
		//�����յ� std::optional����������Ҫ�����Ǳ�ʾһ�����ܲ����ڵ�ֵ��������ͳ��ָ���������Ҫʹ�������ֵ
		//���� nullptr ���ָ�룩����ʾ��ֵ��ʹ�� std::optional ʱ�����ǿ���ʹ�� std::nullopt ����ʽ�ر�ʾ��ֵ��
		//������Ҫͨ������ı�ǻ�Լ������ʾ��ֵ��ͬʱ������ std::optional �����������ȷ�����Կ�����ߴ���Ŀɶ��ԺͰ�ȫ�ԡ�
		//���磬����������еĺ��� OpenFile �ͷ�����һ�����ܴ��ڵ� std::string ���󣬻���һ�������ڵ�ֵ
		//�����յ� std::optional<std::string>���������������߿���ͨ����鷵��ֵ�Ƿ�Ϊ�����жϺ����Ƿ�ɹ������ļ���
		//���ҿ��Ա���ʹ�ô�ͳ�Ĵ�������׳��쳣���������
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}