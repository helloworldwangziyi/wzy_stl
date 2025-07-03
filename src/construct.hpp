#ifndef _WZY_STL_CONSTRUCT_HPP_
#define _WZY_STL_CONSTRUCT_HPP_

#include <new>
#include "type_traits.hpp"
#include "iterator.hpp"

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



}







#endif