#ifndef _WZY_STL_ALLOCATOR_HPP_
#define _WZY_STL_ALLOCATOR_HPP_

#include "../src/construct.hpp"
#include "../src/util.hpp"


namespace wzy_stl
{

template<class T>
class allocator{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
public:
    static T* allocate();
    static T* allocate(size_type n);

    static void deallocate(T* ptr);
    static void deallocate(T* ptr, size_type n);

    static void construct(T* ptr);
    static void construct(T* ptr, const_reference value);
    static void construct(T* ptr, T&& value);

    template<class... Args>
    static void construct(T* ptr, Args&&... args);

    static void destroy(T* ptr);
    static void destroy(T* first, T* last);
};

template<class T>
T* allocator<T>::allocate()
{
    return static_cast<T*>(::operator new(sizeof(T)));
}

template<class T>
T* allocator<T>::allocate(size_type n)
{
    if(n == 0) 
        return nullptr;
    return static_cast<T*>(::operator new(sizeof(T) * n));
}

template<class T>
void allocator<T>::deallocate(T* ptr)
{
    if(ptr == nullptr) 
        return;
    ::operator delete(ptr);
}

template<class T>
void allocator<T>::deallocate(T* ptr, size_type n)
{
    if(n == 0) 
        return;
    ::operator delete(ptr);
}

template<class T>
void allocator<T>::construct(T* ptr)
{
    wzy_stl::construct(ptr);
}

template<class T>
void allocator<T>::construct(T* ptr, const T& value)
{
    wzy_stl::construct(ptr, value);
}

template<class T>
void allocator<T>::construct(T* ptr, T&& value)
{
    wzy_stl::construct(ptr, wzy_stl::move(value));
}

template<class T>
template<class...Args>
void allocator<T>::construct(T* ptr, Args&& ...args)
{
    wzy_stl::construct(ptr, wzy_stl::forward<Args>(args)...);
}

template<class T>
void allocator<T>::destroy(T* ptr)
{
    wzy_stl::destroy(ptr);
}


template<class T>
void allocator<T>::destroy(T* first, T* last)
{
    wzy_stl::destroy(first, last);
}
    
}





#endif