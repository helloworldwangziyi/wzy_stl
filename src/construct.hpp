#ifndef _WZY_STL_CONSTRUCT_HPP_
#define _WZY_STL_CONSTRUCT_HPP_

// 这个文件是用来构造和销毁对象的

#include <new>
#include "type_traits.hpp"
#include "iterator.hpp"
#include "util.hpp"

namespace wzy_stl
{


// construct 构造对象
template<class Ty1>
void construct(Ty1* ptr)
{
    ::new((void*)ptr)Ty1();
}


template<class Ty1, class Ty2>
void construct(Ty1* ptr, const Ty2& value)
{
    ::new((void*)ptr) Ty1(value);
}

template<class Ty1, class ...Args>
void construct(Ty1* ptr, Args&&... args)
{
    ::new((void*)ptr) Ty1(wzy_stl::forward<Args>(args)...);
}


// destroy 销毁对象
template<class Ty>
void destroy_one(Ty* ptr, std::true_type) {}

template<class Ty>
void destroy_one(Ty* pointer, std::false_type)
{
    if(pointer != nullptr)
    {
        pointer->~Ty();
    }
}

template <class Ty>
void destroy(Ty* pointer);

template <class ForwardIter>
void destroy_cat(ForwardIter , ForwardIter, std::true_type){}


template <class ForwardIter>
void destroy_cat(ForwardIter first, ForwardIter last, std::false_type)
{
    for(; first != last; ++first)
    {
        destroy(&first);
    }
}

template <class Ty>
void destroy(Ty* pointer)
{
  destroy_one(pointer, std::is_trivially_destructible<Ty>{});
}

template <class ForwardIter>
void destroy(ForwardIter first, ForwardIter last)
{
  destroy_cat(first, last, std::is_trivially_destructible<
              typename iterator_traits<ForwardIter>::value_type>{});
}


}







#endif