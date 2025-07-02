#ifndef __WZY_STL_ITERATOR_HPP__
#define __WZY_STL_ITERATOR_HPP__

#include <cstddef>
#include "../src/type_traits.hpp"

namespace wzy_stl
{

// 5种迭代器的类型
// 1. 输入迭代器
// 2. 输出迭代器
// 3. 前向迭代器
// 4. 双向迭代器
// 5. 随机访问迭代器
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// iterator 模版
template<class Category, class T, class Distance = ptrdiff_t, 
    class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef Category iterator_category; // 迭代器类型
    typedef T value_type; // 迭代器所指对象的类型
    typedef Distance difference_type; // 两个迭代器之间的距离
    typedef Pointer pointer; // 迭代器所指对象的指针
    typedef Reference reference; // 迭代器所指对象的引用
};

// 判断是否有成员类型 iterator_category c++11
// template<class T>
// struct has_iterator_category
// {
// private:
//     struct two {char a; char b;};
//     template<class U>
//     static two test(...);
//     template<class U>
//     static char test(typename U::iterator_category* = 0);
// public:
//     static const bool value = sizeof(test<T>(0)) == sizeof(char);
// };

// c++17 判断是否有成员类型 iterator_category void_t
// template<class, class = std::void_t<>>
// struct has_iterator_category : std::false_type{};

// template <typename T>
// struct has_iterator_category<T, std::void_t<typename T::iterator_category>> : std::true_type {};


// c++20 判断是否有成员类型 iterator_category
template<class T>
concept has_iterator_category = requires {typename T::iterator_category;};

// 迭代器萃取器
template<class Iterator, bool>
struct iterator_traits_impl{};

// 偏特化 如果bool为true 则有成员类型 则拥有iterator的类型
template<class Iterator>
struct iterator_traits_impl<Iterator, true>
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};


// 要求iterator_category 为input_iterator_tag 或 output_iterator_tag 或者可以隐式转换为input_iterator_tag 或 output_iterator_tag
template<class Iterator, bool>
struct iterator_traits_helper{};

template<class Iterator>
struct iterator_traits_helper<Iterator, true>
 : public iterator_traits_impl<Iterator, 
std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
{

};


// 先判断iterator 是否有成员类型 iterator_category 然后根据iterator_category 的类型 判断是否可以隐式转换为input_iterator_tag 或 output_iterator_tag 都符合才会有相应的成员类型否则没有
template<class Iterator>
struct iterator_traits : public iterator_traits_helper<Iterator, has_iterator_category<Iterator>>{};

// 针对原生指针的偏特化版本
template<class T>
struct iterator_traits<T*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
};

template<class T>
struct iterator_traits<const T*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;
};

template<class T, class U, bool = has_iterator_category<T>>
struct has_iterator_category_of : public wzy_bool_constant<std::is_convertible<typename T::iterator_category, U>::value> {};

template<class T, class U>
struct has_iterator_category_of<T, U, false> : public wzy_false_type {};


template<class Iter>
struct is_exactly_input_iterator : public wzy_bool_constant<
std::is_convertible<typename Iter::iterator_category, input_iterator_tag>::value &&
!std::is_convertible<typename Iter::iterator_category, output_iterator_tag>::value>
{};

template<class Iter>
struct is_input_iterator : public has_iterator_category_of<Iter, input_iterator_tag> {};

template<class Iter>
struct is_output_iterator : public has_iterator_category_of<Iter, output_iterator_tag> {};

template<class Iter>
struct is_forward_iterator : public has_iterator_category_of<Iter, forward_iterator_tag> {};

template<class Iter>
struct is_bidirectional_iterator : public has_iterator_category_of<Iter, bidirectional_iterator_tag> {};

template<class Iter>
struct is_random_access_iterator : public has_iterator_category_of<Iter, random_access_iterator_tag> {};

template<class Iterator>
struct is_iterator : public wzy_bool_constant<is_input_iterator<Iterator>::value || is_output_iterator<Iterator>::value> {};

// 迭代器类型萃取器
// 萃取某个迭代器的 category
template<class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
    typedef typename iterator_traits<Iterator>::iterator_category Category;
    return Category();
}


template<class Iterator>
typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 萃取某个迭代器的 value_type
template<class Iterator>
typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&)
{
    // 返回一个空指针 因为value_type 是类型 不是对象 所以不能返回对象
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// 计算迭代器之间的距离
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
{
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while(first != last)
    {
        ++first;
        ++n;
    }
    return n;
}

// distance 的 random_access_iterator_tag 的版本
template <class RandomIter>
typename iterator_traits<RandomIter>::difference_type
distance_dispatch(RandomIter first, RandomIter last,
                  random_access_iterator_tag)
{
  return last - first;
}

template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
    return distance_dispatch(first, last, iterator_category(first));
}

// 以下函数用于让迭代器前进n个位置
template<class InputIterator, class Distance>
void advance_dispatch(InputIterator& it, Distance n, input_iterator_tag)
{
    while(n--)
    {
        ++it;
    }
}

template<class RandomIter, class Distance>
void advance_dispatch(RandomIter& it, Distance n, random_access_iterator_tag)
{
    it += n;
}

template<class InputIterator, class Distance>
void advance(InputIterator& it, Distance n)
{
    advance_dispatch(it, n, iterator_category(it));
}

template<class Iterator>
class reverse_iterator{
private:
    Iterator current; // 记录对应的正向迭代器
public:
    // 反向迭代器的五种相应类别
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef typename iterator_traits<Iterator>::reference reference;

    typedef Iterator iterator_type; 
    typedef reverse_iterator<Iterator> self;
};



}

#endif