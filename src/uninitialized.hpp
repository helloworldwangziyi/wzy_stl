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
    return wzy_stl::uncheck_uninit_copy(first, last, result, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIter>::value_type>{});
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



}  // namespace wzy_stl

#endif // WZY_STL_UNINITIALIZED_HPP