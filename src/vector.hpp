# ifndef WZ_VECTOR_HPP
# define WZ_VECTOR_HPP



// 模版类vector
#include <initializer_list>
#include "memory.hpp"
#include "util.hpp"
#include "exceptdef.hpp"
#include "algobase.hpp"
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

    template <class Iter, typename std::enable_if<wzy_stl::is_input_iterator<Iter>::value, int>::type = 0>
    vector(Iter first, Iter last)
    {
        WZY_DEBUG(!(last < first));
        range_init(first, last);
    }

    vector(const vector& other)
    {
        range_init(other.begin_, other.end_);
    }

    // 移动构造函数
    vector(vector&& other) noexcept
    :begin_(other.begin_),
    end_(other.end_),
    cap_(other.cap_)
    {
        other.begin_ = nullptr;
        other.end_ = nullptr;
        other.cap_ = nullptr;
    }

    vector(std::initializer_list<value_type> ilist)
    {
        range_init(ilist.begin(), ilist.end());
    }

    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;

    vector& operator=(std::initializer_list<value_type> ilist)
    {
        vector tmp(ilist.begin(), ilist.end());
        swap(tmp);
        return *this;
    }

    ~vector()
    {
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = end_ = cap_ = nullptr;
    }

public:

    // 迭代器相关的操作
    iterator begin() noexcept
    {
        return begin_;
    }

    const_iterator begin() const noexcept
    {
        return begin_;
    }

    iterator end() noexcept
    {
        return end_;
    }

    const_iterator end() const noexcept
    {
        return end_;
    }

    // 反向迭代器
    reverse_iterator rbegin() noexcept
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator(begin());
    }

    const_iterator cbegin() const noexcept
    {
        return begin();
    }

    const_iterator cend() const noexcept
    {
        return end();
    }

    const_reverse_iterator crbegin() const noexcept
    {
        return rbegin();
    }

    const_reverse_iterator crend() const noexcept
    {
        return rend();
    }

    // 容量相关操作
    bool empty() const noexcept
    {
        return begin_ == end_;
    }

    size_type size() const noexcept
    {
        return static_cast<size_type>(end_ - begin_);
    }

    size_type max_size() const noexcept
    {
        return static_cast<size_type>(-1) / sizeof(T);
    }

    size_type capacity() const noexcept
    {
        return static_cast<size_type>(cap_ - begin_);
    }

    void reserve(size_type n);

    void shrink_to_fit();

    void swap(vector& other) noexcept;

    // 访问元素相关操作
    reference operator[](size_type n)
    {
        WZY_DEBUG(n < size());
        return *(begin_ + n);
    }

    const_reference operator[](size_type n) const
    {
        WZY_DEBUG(n < size());
        return *(begin_ + n);
    }

    reference at(size_type n)
    {
        WZY_THROW_OUT_OF_RANGE_IF(n >= size(), "n is out of range");
        return (*this)[n];
    }

    const_reference at(size_type n) const
    {
        WZY_THROW_OUT_OF_RANGE_IF(n >= size(), "n is out of range");
        return (*this)[n];
    }

    reference front()
    {
        WZY_DEBUG(!empty());
        return *begin_;
    }

    const_reference front() const 
    {
        WZY_DEBUG(!empty());
        return *begin_;
    }

    reference back()
    {
        WZY_DEBUG(!empty());
        return *(end_ - 1);
    }

    const_reference back() const 
    {
        WZY_DEBUG(!empty());
        return *(end_ - 1);
    }
    pointer data() noexcept
    {
        return begin_;
    }

    const_pointer data() const noexcept
    {
        return begin_;
    }

    // 修改容器相关操作
    

private:
    void try_init() noexcept; // 初始化

    void init_space(size_type size, size_type cap);

    void fill_init(size_type n, const value_type& value);

    template <class Iter>
    void range_init(Iter first, Iter last);

    void destroy_and_recover(iterator first, iterator last, size_type n);


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

template <class T>
void vector<T>::destroy_and_recover(iterator first, iterator last, size_type n)
{
    // 先调用析构函数
    data_allocator::destroy(first, last);
    // 再释放内存
    data_allocator::deallocate(first, n);
}

template<class T>
void vector<T>::reserve(size_type n)
{
    if(capacity() < n)
    {
        WZY_THROW_LENGTH_ERROR_IF(n > max_size(), "n can't be greater than max_size()");
        
        const auto old_size = size();
        auto tmp = data_allocator::allocate(n);
        wzy_stl::uninitialized_move(begin_, end_, tmp);
        data_allocator::deallocate(begin_, cap_ - begin_);
        begin_ = tmp;
        end_ = begin_ + old_size;
        cap_ = begin_ + n;
    }
}


template<class T>
void vector<T>::swap(vector& other) noexcept
{
    if(this != &other)
    {
        wzy_stl::swap(begin_, other.begin_);
        wzy_stl::swap(end_, other.end_);
        wzy_stl::swap(cap_, other.cap_);
    }
}



}




#endif

