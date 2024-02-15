#pragma once

#include <string>

namespace Hazel {

	class FileDialogs
	{
	public:
		//std::optional<> 是一个 C++17 中引入的数据类型，它可以包含一个类型为 std::string 的对象或者不包含任何对象
		//（即空的 std::optional）。它的主要作用是表示一个可能不存在的值，而不像传统的指针或引用需要使用特殊的值
		//（如 nullptr 或空指针）来表示空值。使用 std::optional 时，我们可以使用 std::nullopt 来显式地表示空值，
		//而不需要通过特殊的标记或约定来表示空值。同时，由于 std::optional 的语义更加明确，所以可以提高代码的可读性和安全性。
		//例如，在这个问题中的函数 OpenFile 就返回了一个可能存在的 std::string 对象，或者一个不存在的值
		//（即空的 std::optional<std::string>）。这样，调用者可以通过检查返回值是否为空来判断函数是否成功打开了文件，
		//并且可以避免使用传统的错误码或抛出异常来处理错误。
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}