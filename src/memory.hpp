#ifndef WZY_STL_MEMORY_HPP
#define WZY_STL_MEMORY_HPP

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.hpp"
#include "allocator.hpp"
#include "construct.hpp"
#include "uninitialized.hpp"

namespace wzy_stl
{

// 获取对象地址
template <class Tp>
constexpr Tp *address_of(Tp &value) noexcept
{
    return &value;
}

// 获取 / 释放 临时缓冲区
template <class T>
pair<T *, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T *)
{
    if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
    {
        len = INT_MAX / sizeof(T);
    }

    while (len > 0)
    {
        T *tmp = static_cast<T *>(malloc(static_cast<size_t>(len) * sizeof(T)));
        if (tmp)
        {
            return pair<T *, ptrdiff_t>(tmp, len);
        }
        len /= 2;
    }
    return pair<T *, ptrdiff_t>(nullptr, 0);
}

template <class T>
pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len)
{
    return get_buffer_helper(len, static_cast<T *>(0));
}

template <class T>
pair<T *, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T *)
{
    return get_buffer_helper(len, static_cast<T *>(0));
}

template <class T>
void release_temporary_buffer(T *ptr)
{
    free(ptr);
}

// --------------------------------------------------------------------------------------
// 类模板 : temporary_buffer
// 进行临时缓冲区的申请与释放
template <class ForwardIter, class T>
class temporary_buffer
{
private:
    ptrdiff_t original_len; // 缓冲区申请的大小
    ptrdiff_t len;          // 缓冲区实际的大小
    T *buffer;              // 指向缓冲区的指针
public:
    // 构造、析构函数
    temporary_buffer(ForwardIter first, ForwardIter last);

    ~temporary_buffer()
    {
        wzy_stl::destroy(buffer, buffer + len);
        free(buffer);
    }
public:

    ptrdiff_t size()  const noexcept { return len;}
    ptrdiff_t requested_size() const noexcept { return original_len; }
    T* beigin()  noexcept { return buffer; }
    T* end()  noexcept {return buffer + len;}

private:
    void allocate_buffer();
    void initialize_buffer(const T& value, std::true_type) {}
    void initialize_buffer(const T& value, std::false_type)
    {
        wzy_stl::uninitialized_fill_n(buffer, len, value);
    }

private:
    temporary_buffer(const temporary_buffer&);
    void operator=(const temporary_buffer&);
};

// 构造函数
template<class ForwardIter, class T>
temporary_buffer<ForwardIter , T>::
temporary_buffer(ForwardIter first, ForwardIter last)
{
    try
    {
        len = wzy_stl::distance(first, last);
        allocate_buffer();
        if(len  > 0)
        {
            initialize_buffer(*first, std::is_trivially_default_constructible<T>{});
        }
    }
    catch(...)
    {
        free(buffer);
        buffer = nullptr;
        len = 0;
    }
}

template<class ForwardIter, class T>
void temporary_buffer<ForwardIter, T>::allocate_buffer()
{
    original_len = len;
    if(len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
    {
        len = INT_MAX / sizeof(T);
    }

    while(len > 0)
    {
        buffer = static_cast<T*>(malloc(static_cast<size_t>(len) * sizeof(T)));
        if(buffer)
        {
            break;
        }
        len /= 2;
    }
}

// --------------------------------------------------------------------------------------
// 模板类: auto_ptr
// 一个具有严格对象所有权的小型智能指针

}

#endif // WZY_STL_MEMORY_HPP