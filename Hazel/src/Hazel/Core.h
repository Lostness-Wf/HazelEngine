#pragma once

//定义dll导出导入
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif //HZ_BUILD_DLL
#else
	#error Hazel only support Windows!
#endif // HZ_PLATFORM_WINDOWS

/*这两个宏用于在调试模式下进行断言检查。如果定义了 HZ_ENABLE_ASSERTS 符号，
则这两个宏会检查给定的条件 x 是否为真。如果条件为假，则会调用 HZ_ERROR 或
HZ_CORE_ERROR 宏输出错误信息，并调用 __debugbreak 函数触发断点。
如果没有定义 HZ_ENABLE_ASSERTS，那么这两个宏不会执行任何操作。*/
#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif // HZ_PLATFORM_WINDOWS

#define BIT(x) (1 << x)