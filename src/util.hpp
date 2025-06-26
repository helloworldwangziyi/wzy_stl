#ifndef WZY_STL_UTIL_HPP
#define WZY_STL_UTIL_HPP

// 工具类实现一些move swap forward等函数

#include <cstddef>

namespace wzy_stl
{

// move
template<typename T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept
{
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// forward
template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& arg) noexcept
{
    return static_cast<T&&>(arg);
}

template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type &&arg) noexcept
{
    static_assert(!std::is_lvalue_reference<T>::value, "template argument"
    " substituting T is an lvalue reference type");
    return static_cast<T&&>(arg);
}

}


#endif // WZY_STL_UTIL_HPP
