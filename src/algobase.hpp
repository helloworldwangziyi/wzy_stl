#ifndef __ALGOBASE_HPP__
#define __ALGOBASE_HPP__

#include <cstring>

#include "iterator.hpp"
#include "util.hpp"

namespace wzy_stl{

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

/*****************************************************************************************/
// max
// 取二者中的较大值，语义相等时保证返回第一个参数
/*****************************************************************************************/
template<class T>
const T& max(const T& a, const T& b)
{
    return a < b ? b : a;
}

template<class T, class Compare>
const T& max(const T& lhs, const T& rhs, Compare comp)
{
    return comp(lhs, rhs) ? rhs : lhs;
}
/*****************************************************************************************/
// min 
// 取二者中的较小值，语义相等时保证返回第一个参数
/*****************************************************************************************/
template <class T>
const T& min(const T& lhs, const T& rhs)
{
  return rhs < lhs ? rhs : lhs;
}

// 重载版本使用函数对象 comp 代替比较操作
template <class T, class Compare>
const T& min(const T& lhs, const T& rhs, Compare comp)
{
  return comp(rhs, lhs) ? rhs : lhs;
}

/*****************************************************************************************/
// iter_swap
// 将两个迭代器所指对象对调
/*****************************************************************************************/
template <class FIter1, class FIter2>
void iter_swap(FIter1 lhs, FIter2 rhs)
{
  wzy_stl::swap(*lhs, *rhs);
}
/*****************************************************************************************/
// copy
// 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内
/*****************************************************************************************/
// input_iterator_tag 版本
template <class InputIter, class OutputIter>
OutputIter 
unchecked_copy_cat(InputIter first, InputIter last, OutputIter result, wzy_stl::input_iterator_tag)
{
    for(; first != last; ++result, ++first)
    {
        *result = *first;
    }
    return result;
}

// ramdom_access_iterator_tag 版本
template <class RandomIter, class OutputIter>
OutputIter 
unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result,
                   wzy_stl::random_access_iterator_tag)
{
  for (auto n = last - first; n > 0; --n, ++first, ++result)
  {
    *result = *first;
  }
  return result;
}

template <class InputIter, class OutputIter>
OutputIter unchecked_copy(InputIter first, InputIter last, OutputIter result)
{
    return unchecked_copy_cat(first, last, result, wzy_stl::iterator_category(first));
}

template<class Tp, class Up>
concept TriviallyCopyable = std::is_same_v<typename std::remove_const<Tp>::type, Up> &&
                            std::is_trivially_copy_assignable<Up>::value;

template<class Tp, class Up>
        requires TriviallyCopyable<Tp, Up>
Up* unchecked_copy(Tp* first, Tp* last, Up* result)
{
    const auto n = static_cast<size_t>(last - first);
    if(n != 0)
      std::memmove(result, first, n * sizeof(Tp));
    return result + n;
}

template<class InputIter,class OutputIter>
OutputIter copy(InputIter first, InputIter last, OutputIter result)
{
  return unchecked_copy(first, last, result);
}

/*****************************************************************************************/
// copy_backward
// 将 [first, last)区间内的元素拷贝到 [result - (last - first), result)内
/*****************************************************************************************/
// unchecked_copy_backward_cat 的 bidirectional_iterator_tag 版本

/*****************************************************************************************/
// copy_n
// 把 [first, first + n)区间上的元素拷贝到 [result, result + n)上
// 返回一个 pair 分别指向拷贝结束的尾部
/*****************************************************************************************/
template<class InputIter, class Size, class OutputIter>
wzy_stl::pair<InputIter, OutputIter>
unchecked_uninit_copy_n(InputIter first, Size n , OutputIter result, wzy_stl::input_iterator_tag)
{
  for(; n > 0; --n, ++first, ++result)
  {
    *result = *first;
  }
  return wzy_stl::pair<InputIter, OutputIter>(first, result);
}

template <class RandomIter, class Size, class OutputIter>
wzy_stl::pair<RandomIter, OutputIter>
unchecked_uninit_copy_n(RandomIter first, Size n, OutputIter result, 
                 wzy_stl::random_access_iterator_tag)
{
  auto last = first + n;
  return wzy_stl::pair<RandomIter, OutputIter>(last, wzy_stl::copy(first, last, result));
}

template <class InputIter, class Size, class OutputIter>
wzy_stl::pair<InputIter, OutputIter> 
copy_n(InputIter first, Size n, OutputIter result)
{
  return wzy_stl::unchecked_uninit_copy_n(first, n, result,
                                        std::is_trivially_copy_assignable<
                                        typename iterator_traits<InputIter>::
                                        value_type>{});
}
/*****************************************************************************************/
// uninitialized_fill
// 在 [first, last) 区间内填充元素值
/*****************************************************************************************/
template<class ForwardIter, class T>
void
unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type)
{
  wzy_stl::fill(first, last, value);
}

}

#endif