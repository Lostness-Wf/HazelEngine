#pragma once

//����dll��������
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif //HZ_BUILD_DLL
#else
	#error Hazel only support Windows!
#endif // HZ_PLATFORM_WINDOWS

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif //HZ_DEBUG

/*�������������ڵ���ģʽ�½��ж��Լ�顣��������� HZ_ENABLE_ASSERTS ���ţ�
���������������������� x �Ƿ�Ϊ�档�������Ϊ�٣������� HZ_ERROR ��
HZ_CORE_ERROR �����������Ϣ�������� __debugbreak ���������ϵ㡣
���û�ж��� HZ_ENABLE_ASSERTS����ô�������겻��ִ���κβ�����*/
#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif // HZ_PLATFORM_WINDOWS

#define BIT(x) (1 << x)

//std::placeholders::_1 ��һ��ռλ���������ڱ�ʾ std::bind �����󶨵ĺ����ĵ�һ��������
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)