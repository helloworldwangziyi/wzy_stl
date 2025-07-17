#ifndef WZY_STL_UNINITIALIZED_HPP
#define WZY_STL_UNINITIALIZED_HPP

#include "algobase.hpp"
#include "construct.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
#include "util.hpp"

namespace wzy_stl{

/*****************************************************************************************/
// uninitialized_copy
// 把 [first, last) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
/*****************************************************************************************/
template<class InputIterator, class ForwardIterator>
ForwardIterator 
unchecked_uninit_copy(InputIterator first, InputIterator last, ForwardIterator result, std::true_type)
{
    return wzy_stl::copy(first, last ,result);
}

template<class InputIter, class ForwardIter>
ForwardIter 
unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type)
{
    auto cur = result;
    try
    {
        for(; first != last; ++cur, ++first)
        {
            wzy_stl::construct(&*cur, *first);
        }
    }
    catch(...)
    {
        for(; result != cur; --cur)
        {
            wzy_stl::destroy(&*cur);
        }
    }
    return cur;
}

template<class InputIter, class ForwardIter>
ForwardIter 
uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
{
    return wzy_stl::unchecked_uninit_copy(first, last, result, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
}

/*****************************************************************************************/
// uninitialized_copy_n
// 把 [first, first + n) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
/*****************************************************************************************/
template<class InpIter, class Size, class ForwardIter>
ForwardIter 
unchecked_uninit_copy_n(InpIter first, Size n, ForwardIter result, std::true_type)
{
    return wzy_stl::copy_n(first, n, result);
}

template<class InputIter, class Size, class ForwardIter>
ForwardIter 
unchecked_uninit_copy_n(InputIter first, Size n, ForwardIter result, std::false_type)
{
    auto cur = result;
    try{
        for(; n > 0; --n, ++cur, ++first)
        {
            // 因为cur可能是迭代器，所以需要使用&*cur来获取迭代器指向的元素
            wzy_stl::construct(&*cur, *first);
        }
    }
    catch(...)
    {
        for(; result != cur; --cur)
        {
            wzy_stl::destroy(&*cur);
        }
    }
    return cur;
}

template<class InputIter, class Size, class ForwardIter>
ForwardIter
uninitialized_copy_n(InputIter first, Size n, ForwardIter result)
{
    return wzy_stl::unchecked_uninit_copy_n(first, n, result,
    std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
}

/*****************************************************************************************/
// uninitialized_fill
// 在 [first, last) 区间内填充元素值
/*****************************************************************************************/
template<class ForwardIter, class T>
void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type)
{
    wzy_stl::fill(first, last, value);
}

template<class ForwardIter, class T>
void unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::false_type)
{
    auto cur = first;
    try{
        for(; cur != last; ++cur)
        {
            wzy_stl::construct(&*cur, value);
        }
    }
    catch(...)
    {
        for(; first != cur; ++first)
        {
            wzy_stl::destroy(&*first);
        }
    }
}

template<class ForwardIter, class T>
void uninitialized_fill(ForwardIter first, ForwardIter last, const T& value)
{
    wzy_stl::unchecked_uninit_fill(first, last, value,
    std::is_trivially_copy_constructible<typename iterator_traits<ForwardIter>::value_type>{});
}

/*****************************************************************************************/
// uninitialized_fill_n
// 从 first 位置开始，填充 n 个元素值，返回填充结束的位置
/*****************************************************************************************/
template<class ForwardIter, class Size, class T>
ForwardIter
unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::true_type)
{
    return wzy_stl::fill_n(first, n, value);
}

template<class ForwardIter, class Size, class T>
ForwardIter
unchecked_uninit_fill_n(ForwardIter first, Size n, const T& value, std::false_type)
{
    auto cur = first;
    try{
        for(; n > 0; --n, ++cur)
        {
            wzy_stl::construct(&*cur, value);
        }
    }
    catch(...)
    {
        for(; first != cur; ++first)
        {
            wzy_stl::destroy(&*first);
        }
    }
    return cur;
}

template<class ForwardIter, class Size, class T>
ForwardIter
uninitialized_fill_n(ForwardIter first, Size n, const T& value)
{
    return wzy_stl::unchecked_uninit_fill_n(first, n, value,
    std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
}

/*****************************************************************************************/
// uninitialized_move
// 把[first, last)上的内容移动到以 result 为起始处的空间，返回移动结束的位置
/*****************************************************************************************/
template<class InputIter, class ForwardIter>
ForwardIter
unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type)
{
    return wzy_stl::move(first, last, result);
}

template<class InputIter, class ForwardIter>
ForwardIter
unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type)
{
    ForwardIter cur = result;
    try{
        for(; first != last; ++cur, ++first)
        {
            wzy_stl::construct(&*cur, wzy_stl::move(*first));
        }
    }
    catch(...)
    {
        wzy_stl::destroy(result, cur);
    }
    return cur;
}

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result)
{
  return wzy_stl::unchecked_uninit_move(first, last, result,
                                      std::is_trivially_move_assignable<
                                      typename iterator_traits<InputIter>::
                                      value_type>{});
}

/*****************************************************************************************/
// uninitialized_move_n
// 把[first, first + n)上的内容移动到以 result 为起始处的空间，返回移动结束的位置
/*****************************************************************************************/

template<class InputIter, class Size, class ForwardIter>
ForwardIter
unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::true_type)
{
    return wzy_stl::move(first, n, result);
}

template<class InputIter, class Size, class ForwardIter>
ForwardIter
unchecked_uninit_move_n(InputIter first, Size n, ForwardIter result, std::false_type)
{
    auto cur = result;
    try
    {
        for(; n > 0; --n, ++cur, ++first)
        {
            wzy_stl::construct(&*cur, wzy_stl::move(*first));
        }
    }
    catch(...)
    {
        for(; result != cur; ++result)
        {
            wzy_stl::destroy(&*result);
        }
    }
    return cur;
}

template <class InputIter, class Size, class ForwardIter>
ForwardIter uninitialized_move_n(InputIter first, Size n, ForwardIter result)
{
  return wzy_stl::unchecked_uninit_move_n(first, n, result,
                                        std::is_trivially_move_assignable<
                                        typename iterator_traits<InputIter>::
                                        value_type>{});
}

}  // namespace wzy_stl

#endif // WZY_STL_UNINITIALIZED_HPP