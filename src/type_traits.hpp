#ifndef __WZY_STL_TYPE_TRAITS_HPP__
#define __WZY_STL_TYPE_TRAITS_HPP__

// 这个文件用于提取类型信息

namespace wzy_stl
{

template<class T, T v>
struct wzy_integral_constant
{
    static constexpr T value = v;
};


template<bool B>
using wzy_bool_constant = wzy_integral_constant<bool, B>;

typedef wzy_bool_constant<true> wzy_true_type;
typedef wzy_bool_constant<false> wzy_false_type;

/************************************ 类型判断 ************************************/
template<class T1, class T2>
struct pair;

template<class T>
struct is_pair : wzy_false_type{};

template<class T1, class T2>
struct is_pair<wzy_stl::pair<T1, T2>> : wzy_true_type{};



}




#endif // __WZY_STL_TYPE_TRAITS_HPP__