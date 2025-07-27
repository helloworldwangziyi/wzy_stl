# ifndef WZ_VECTOR_HPP
# define WZ_VECTOR_HPP



// 模版类vector
#include <initializer_list>
#include "memory.hpp"
#include "util.hpp"
#include "exceptdef.hpp"
#include "algo.hpp"


namespace wzy_stl
{

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

// 模版类 vector
// 模版参数 T 代表类型
template <class T>
class vector
{
    static_assert(!std::is_same<bool, T>::value, "vector<bool> is not supported");
public:
    // vector 的嵌套类别定义
    typedef wzy_stl::allocator<T> allocator_type;
    typedef wzy_stl::allocator<T> data_allocator;
    typedef typename allocator_type::value_type value_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef value_type *iterator;
    typedef const value_type *const_iterator;
    typedef wzy_stl::reverse_iterator<iterator> reverse_iterator;
    typedef wzy_stl::reverse_iterator<const_iterator> const_reverse_iterator;

    allocator_type get_allocator() {return data_allocator();}
private:
    iterator begin_; // 表示目前使用空间的头部
    iterator end_;   // 表示目前使用空间的尾部
    iterator cap_;   // 表示目前存储空间的尾部

public:
    // 构造函数 复制 移动 析构函数
    vector() noexcept
    { try_init();}

    explicit vector(size_type n)
    {
        fill_init(n, value_type());
    }

    vector(size_type n, const value_type& value)
    {
        fill_init(n ,value);
    }

private:
    void try_init() noexcept; // 初始化

    void init_space(size_type size, size_type cap);

    void fill_init(size_type n, const value_type& value);

    template <class Iter>
    void range_init(Iter first, Iter last);


};


template <class T>
void vector<T>::try_init() noexcept
{
    try
    {
        begin_ = data_allocator::allocate(16);
        end_ = begin_;
        cap_ = begin_ + 16;
    }
    catch(...)
    {
        begin_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
    }   
}

template <class T>
void vector<T>::init_space(size_type size, size_type cap)
{
    try
    {
        begin_ = data_allocator::allocate(cap);
        end_ = begin_ + size;
        cap_ = begin_ + cap;
    }
    catch(...)
    {
        begin_ = nullptr;
        end_ = nullptr;
        cap_ = nullptr;
        throw;
    }
    
}

template <class T>
void vector<T>::fill_init(size_type n, const value_type& value)
{
    const size_type init_size = wzy_stl::max(static_cast<size_type>(16, n));
    init_space(n , init_size);
    wzy_stl::uninitialized_fill_n(begin_, n , value);
}

template <class T>
template <class Iter>
void vector<T>::range_init(Iter first, Iter last)
{
    const size_type len = wzy_stl::distance(first, last);
    const size_type init_size = wzy_stl::max(len, static_cast<size_type>(16));
    init_space(len, init_size);
    wzy_stl::uninitialized_copy(first, last, begin_);
}



}




#endif

