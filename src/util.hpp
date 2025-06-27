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

template<typename T>
void swap(T& lhs, T& rhs)
{
    auto tmp(wzy_stl::move(lhs));
    lhs = wzy_stl::move(rhs);
    rhs = wzy_stl::move(tmp);
}

template<typename ForwardIter1, typename ForwardIter2>
ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2)
{
    for(; first1 != last1; ++first1, (void)++first2)
    {
        wzy_stl::swap(*first1, *first2);
    }
    return first2;
}

template<typename T, size_t N>
void swap(T(&a)[N], T(&b)[N])
{
    wzy_stl::swap_range(a, a + N, b);
}


// 结构体模板 pair 
// 两个模板参数分别表示两个数据的类型
// 用first 和 second 来分别取出第一个和第二个数据
template<typename T1, typename T2>
struct pair
{
    typedef T1 first_type;
    typedef T2 second_type;

    first_type first;
    second_type second;

    // default constructiable
    // c++11 enable_if
    // template <class Other1 = T1, class Other2 = T2,
    //     typename = typename std::enable_if<
    //     std::is_default_constructible<Other1>::value &&
    //     std::is_default_constructible<Other2>::value, void>::type>
    //     constexpr pair()
    //     : first(), second()
    // {
    // }

    // default constructiable
    // c++20 新标准 concept
    template<class Other1 = T1, class Other2 = T2>
    requires std::is_default_constructible_v<Other1> && std::is_default_constructible_v<Other2>
    constexpr pair() : first(), second()
    {
    }

    // c++14 enable_if_t 允许隐式转换
    // template<typename U1 = T1, typename U2 = T2,
    // typename std::enable_if_t<
    // std::is_copy_constructible<U1>::value && 
    // std::is_copy_constructible<U2>::value && 
    // (std::is_convertible<const U1&, T1>::value &&
    // std::is_convertible<const U2&, T2>::value), int> = 0>
    // constexpr pair(const U1& x, const U2& y) : first(x), second(y)
    // {
    // }

    // c++20 新标准 concept requires 允许隐式转换
    template<class Other = T1, class Other2 = T2>
    requires std::is_constructible_v<T1, Other> && 
    std::is_constructible_v<T2, Other2> && 
    (std::is_convertible<const Other&, T1>::value &&
    std::is_convertible<const Other2&, T2>::value)
    constexpr pair(const Other& x, const Other2& y) : first(x), second(y)
    {
    }

    // c++14 新标准 不允许隐式转换
    // template<typename U1 = T1, typename U2 = T2, 
    // typename std::enable_if_t<
    // std::is_copy_constructible_v<U1> &&
    // std::is_copy_constructible_v<U2> && 
    // (!std::is_convertible<const U1&, T1>::value || !std::is_convertible<const U2&, T2>::value), int> = 0>
    // explicit constexpr pair(const U1& x, const U2& y) : first(x), second(y)
    // {
    // }

    // c++20 新标准 concept requires 不允许隐式转换
    template<class Other = T1, class Other2 = T2>
    requires std::is_constructible_v<T1, Other> && 
    std::is_constructible_v<T2, Other2> && 
    (!std::is_convertible<const Other&, T1>::value || !std::is_convertible<const Other2&, T2>::value)
    explicit constexpr pair(const Other& x, const Other2& y) : first(x), second(y)
    {
    }


    // c++14 支持临时对象直接构造（完美转发） 隐式转换
    // template<typename U1, typename U2,
    // typename std::enable_if_t<
    // std::is_constructible<T1, U1>::value &&
    // std::is_constructible<T2, U2>::value &&
    // std::is_convertible<U1&&, T1>::value &&
    // std::is_convertible<U2&&, T2>::value,
    // int> = 0>
    // constexpr pair(U1&& x, U2&& y) : first(wzy_stl::forward<U1>(x)), second(wzy_stl::forward<U2>(y))
    // {
    // }

    // c++20 新标准 concept requires 支持临时对象直接构造（完美转发） 隐式转换
    template<class Other = T1, class Other2 = T2>
    requires std::is_constructible_v<T1, Other> && 
    std::is_constructible_v<T2, Other2> && 
    std::is_convertible_v<Other&&, T1> &&
    std::is_convertible_v<Other2&&, T2>
    constexpr pair(Other&& x, Other2&& y) : first(wzy_stl::forward<Other>(x)), second(wzy_stl::forward<Other2>(y))
    {

    }

    // c++14 支持临时对象直接构造（完美转发） 非隐式转换
    // template<typename U1 = T1, typename U2 = T2, 
    // typename std::enable_if_t<
    // std::is_constructible_v<U1, T1> && 
    // std::is_constructible_v<U2, T2> && 
    // (!std::is_convertible_v<U1&& , T1> ||
    // !std::is_convertible_v<U2&&, T2>),int> = 0>
    // explicit constexpr pair(U1&& x, U2&& y) : first(wzy_stl::forward<U1>(x)), second(wzy_stl::forward<U2>(y))
    // {
       
    // }

    // c++20 新标准 concept requires 支持临时对象直接构造（完美转发） 非隐式转换
    template<class Other = T1, class Other2 = T2>
    requires std::is_constructible_v<T1, Other> && 
    std::is_constructible_v<T2, Other2> && 
    (!std::is_convertible_v<Other&&, T1> ||
    !std::is_convertible_v<Other2&&, T2>)
    explicit constexpr pair(Other&& x, Other2&& y) : first(wzy_stl::forward<Other>(x)), second(wzy_stl::forward<Other2>(y))
    {

    }



    pair(const pair& rhs) = default;
    pair(pair&& rhs) = default;
};

}


#endif // WZY_STL_UTIL_HPP
