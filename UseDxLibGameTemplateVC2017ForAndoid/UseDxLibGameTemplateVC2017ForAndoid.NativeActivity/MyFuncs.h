#pragma once
#include <string>
#include <sstream>
#include <type_traits>

namespace MyFuncs {
	/**
	 * stringstreamに入れることができる値をstringに変換
	 */
	template<typename T , typename T2 = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	std::string to_string(const T& v);
	template<typename T, typename T2>
	std::string to_string(const T& v)
	{
		std::stringstream ss;
		ss << v;
		return ss.str();
	}
}