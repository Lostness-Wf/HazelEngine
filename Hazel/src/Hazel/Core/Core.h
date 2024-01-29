#pragma once

#include <memory>

//定义dll导出导入
#ifdef HZ_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
#ifdef HZ_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif //HZ_BUILD_DLL
#else
#define HAZEL_API
#endif

#else
#error Hazel only support Windows!
#endif // HZ_PLATFORM_WINDOWS

#ifdef HZ_DEBUG
#define HZ_ENABLE_ASSERTS
#endif //HZ_DEBUG

#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define HZ_ASSERT(x, ...)
#define HZ_CORE_ASSERT(x, ...)
#endif // HZ_PLATFORM_WINDOWS

#define BIT(x) (1 << x)

//std::placeholders::_1 是一个占位符，它用于表示 std::bind 函数绑定的函数的第一个参数。
#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}