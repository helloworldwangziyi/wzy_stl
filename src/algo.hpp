#ifndef __WZY_STL_ALGO_HPP__
#define __WZY_STL_ALGO_HPP__

#include <cstddef>
#include <ctime>

#include "algobase.hpp"
#include "memory.hpp"


namespace wzy_stl
{

/*****************************************************************************************/
// reverse
// 将[first, last)区间内的元素反转
/*****************************************************************************************/
// reverse_dispatch 的 bidirectional_iterator_tag 版本
template <class BidirectionalIter>
void reverse_dispatch(BidirectionalIter first, BidirectionalIter last, bidirectional_iterator_tag)
{
    while(true)
    {
        if(first == last || first == --last)
        {
            return;
        } 
        wzy_stl::iter_swap(first++, last);
    }
}


template <class RandomIter>
void reverse_dispatch(RandomIter first, RandomIter last, random_access_iterator_tag)
{
    while(first < last)
    {
        wzy_stl::iter_swap(first++, --last);
    }
}


template <class BidirectionalIter>
void reverse(BidirectionalIter first, BidirectionalIter last)
{
    wzy_stl::reverse_dispatch(first, last, wzy_stl::iterator_category(first));
}


}

#endif