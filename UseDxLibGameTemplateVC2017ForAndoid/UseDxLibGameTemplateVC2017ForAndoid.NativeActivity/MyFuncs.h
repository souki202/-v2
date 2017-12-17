#pragma once
#include <string>
#include <sstream>
#include <type_traits>
#include <algorithm>
#undef max
#undef min

namespace MyFuncs {
	/**
	 * stringstreamに入れることができる値をstringに変換
	 */
	template<typename T , typename T2 = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	std::string to_string(const T& v);

	/**
	* 縦横の大きさを,アスペクト比を保持して指定範囲内で拡大.
	*/
	template<typename T, typename T2 = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	float calcScaleInWindow(const T& x, const T& y, const T& wndX, const T& wndY, bool isContain = true);

	template<typename T, typename T2>
	std::string to_string(const T& v)
	{
		std::stringstream ss;
		ss << v;
		return ss.str();
	}

	template<typename T, typename T2>
	float calcScaleInWindow(const T & x, const T & y, const T & wndX, const T & wndY, bool isContain)
	{
		if (x <= static_cast<T>(0) || y <= static_cast<T>(0) 
			|| wndX <= static_cast<T>(0) || wndY <= static_cast<T>(0)) return static_cast<T>(0);
		if (isContain) return std::min(wndX / x, wndY / y);
		return std::max(wndX / x, wndY / y);
	}

}