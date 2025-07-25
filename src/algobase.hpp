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

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                            BidirectionalIter2 result, wzy_stl::bidirectional_iterator_tag)
{
  while(first != last)
  {
    *(--result) = *(--last);
  }
  return result;
}

// random_access_iterator_tag 版本
template <class RandomIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_copy_backward_cat(RandomIter1 first, RandomIter1 last, 
                            BidirectionalIter2 result, wzy_stl::random_access_iterator_tag)
{
  for(auto n = last - first; n > 0; n--)
  {
    *(--result) = *(--last);
  }
  return result;
}

template <class BidIterectionalIter1, class BidIterectionalIter2>
BidIterectionalIter2
unchecked_copy_backward(BidIterectionalIter1 first, BidIterectionalIter1 last, BidIterectionalIter2 result)
{
  return unchecked_copy_backward_cat(first, last, result, wzy_stl::iterator_category(first));
}

// 为平凡拷贝提供特化版本
template <class Tp, class Up>
concept Trivially_copyable = std::is_same_v<typename std::remove_const<Tp>::type, Up> && std::is_trivially_copy_assignable<Up>::value;

template <class Tp, class Up>
requires Trivially_copyable<Tp, Up>
Up* unchecked_copy_backward(Tp* first, Tp* last, Up* result)
{
  const auto n = static_cast<size_t>(last - first);
  if(n != 0)
  {
    result -= n;
    std::memmove(result, first, n * sizeof(Up));
  }
  return result;
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
{
  return unchecked_copy_backward(first, last, result);
}

/*****************************************************************************************/
// copy_if
// 把[first, last)内满足一元操作 unary_pred 的元素拷贝到以 result 为起始的位置上
/*****************************************************************************************/
template <class InputIter, class OutputIter, class UnaryPredicate>
OutputIter
copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred)
{
  for(; first != last; ++first)
  {
    if(unary_pred(*first))
    {
      *result++ = *first;
    }
  }
  return result;
}

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
// move
// 把 [first, last)区间内的元素移动到 [result, result + (last - first))内
/*****************************************************************************************/
// input_iterator_tag 版本
template<class InputIter, class OutputIter>
OutputIter
unchecked_move_cat(InputIter first, InputIter last, OutputIter result, 
                   wzy_stl::input_iterator_tag)
{
  for(; first != last; ++first, ++result)
  {
    *result = wzy_stl::move(*first);
  }
  return result;
}

// random_access_iterator_tag 版本
template <class RandomIter, class OutputIter>
OutputIter
unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result,
                   wzy_stl::random_access_iterator_tag)
{
  auto n = last - first;
  for(; n > 0; --n, ++first, ++result)
  {
    *result = wzy_stl::move(*first);
  }
  return result;
}

template<class InputIter , class OutputIter>
OutputIter 
unchecked_move(InputIter first, InputIter last, OutputIter result)
{
  return unchecked_move_cat(first, last, result, iterator_category(first));
}


template <class InputIter, class OutputIter>
OutputIter
move(InputIter first, InputIter last, OutputIter result)
{
  return unchecked_move(first, last, result);
}

/*****************************************************************************************/
// move_backward
// 将 [first, last)区间内的元素移动到 [result - (last - first), result)内
/*****************************************************************************************/
// bidirectional_iterator_tag 版本
template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter2 last, 
                            BidirectionalIter2 result, wzy_stl::bidirectional_iterator_tag)
{
  while(first != last)
  {
    *(--result) = wzy_stl::move(*(--last));
  }
  return result;
}

// random_access_iterator_tag 版本
template <class RandomIter1, class RandomIter2>
RandomIter2
unchecked_move_backward_cat(RandomIter1 first, RandomIter1 last,
                            RandomIter2 result, wzy_stl::random_access_iterator_tag)
{
  auto n = last - first;
  for(; n > 0; --n)
  {
    *--result = wzy_stl::move(*--last);
  }
  return result;
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_move_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                        BidirectionalIter2 result)
{
  return unchecked_move_backward_cat(first, last, result, iterator_category(first));
}

// 为 trivially_move_assignable 类型提供特化版本
template <class Tp, class Up>
concept Trivially_moveable = std::is_same_v<typename std::remove_const<Tp>::type, Up> && std::is_trivially_move_assignable<Up>::value;

template <class Tp, class Up>
requires Trivially_moveable<Tp, Up>
Up* unchecked_move_backward(Tp* first, Tp* last, Up* result)
{
  const size_t n = static_cast<size_t>(last - first);
  if(n != 0)
  {
    result -= n;
    std::memmove(result, first, n * sizeof(Up));
  }
  return result;
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
{
  return unchecked_move_backward(first, last, result);
}

/*****************************************************************************************/
// equal
// 比较第一序列在 [first, last)区间上的元素值是否和第二序列相等
/*****************************************************************************************/
template <class InputIter1, class InputIter2>
bool equal(InputIter1 first1, InputIter2 last1, InputIter2 first2)
{
  for(; first1 != last1; ++first1, ++first2)
  {
    if(*first1 != *first2)
    {
      return false;
    }
  }
  return true;
}

template <class InputIter1, class InputIter2, class Compared>
bool equal(InputIter1 first1, InputIter2 last1, InputIter2 first2, Compared comp)
{
  for(; first1 != last1; ++first1, ++first2)
  {
    if(!comp(*first1, *first2))
    {
      return false;
    }
  }
  return true;
}

/*****************************************************************************************/
// fill_n
// 从 first 位置开始填充 n 个值
/*****************************************************************************************/
template <class OutputIter, class Size, class Tp>
OutputIter unchecked_fill_n(OutputIter first, Size n, const Tp& value)
{
  for(; n > 0; --n, ++first)
  {
    *first = value;
  }
  return first;
}

// 为 one_byte 类型提供特例化版本
template <class Tp, class Size, class Up>
concept One_byte = std::is_integral<Tp>::value && 
                    sizeof(Tp) == 1 &&
                    !std::is_same<Tp, bool>::value && 
                    std::is_integral<Up>::value && 
                    sizeof(Up) == 1;

template <class Tp, class Size, class Up>
requires One_byte<Tp, Size, Up>
Up* unchecked_fill_n(Tp* first, Size n, Up value)
{
  if(n > 0)
  {
    std::memset(first, (unsigned char)value, n);
  }
  return first + n;
}  

template <class OutputIter, class Size, class T>
OutputIter fill_n(OutputIter first, Size n, const T&  value)
{
  return unchecked_fill_n(first, n, value);
}

/*****************************************************************************************/
// fill
// 为 [first, last)区间内的所有元素填充新值
/*****************************************************************************************/
template<class ForwardIter, class T>
void fill_cat(ForwardIter first, ForwardIter last, const T& value,
              wzy_stl::forward_iterator_tag)
{
  for(; first != last; ++first)
  {
    *first = value;
  }
}

template <class RandomIter, class T>
void fill_cat(RandomIter first, RandomIter last, const T& value,
              wzy_stl::random_access_iterator_tag)
{
  auto n = last - first;
  fill_n(first, n, value);
}

template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T& value)
{
  fill_cat(first, last, value, iterator_category(first));
}

/*****************************************************************************************/
// lexicographical_compare
// 以字典序排列对两个序列进行比较，当在某个位置发现第一组不相等元素时，有下列几种情况：
// (1)如果第一序列的元素较小，返回 true ，否则返回 false
// (2)如果到达 last1 而尚未到达 last2 返回 true
// (3)如果到达 last2 而尚未到达 last1 返回 false
// (4)如果同时到达 last1 和 last2 返回 false
/*****************************************************************************************/
template <class InputIter1, class InputIter2>
bool lexicographical_compare(InputIter1 first1, InputIter2 last1, InputIter2 first2, InputIter2 last2)
{
  for(; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if(*first1 < * first2)
    {
      return true;
    }
    if(*first2 < * first1)
    {
      return false;
    }
  }

  return first1 == last1 && first2 != last2;
}

// 重载版本使用函数对象 comp 代替比较操作
template <class InputIter1, class InputIter2, class Compared>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1, 
                             InputIter2 first2, InputIter2 last2, Compared comp)
{
  for(; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if(comp(*first1, *first2))
    {
      return true;
    }
    if(comp(*first2, *first1))
    {
      return false;
    }
  }
  return first1 == last1 && first2 != last2;
}


// 针对const unsigned char* 的特化版本
bool lexicographical_compare(const unsigned char* first1, 
                             const unsigned char* last1,
                             const unsigned char* first2,
                             const unsigned char* last2)
{
  const auto len1 = last1 - first1;
  const auto len2 = last2 - first2;

  // 先比较长度相同的部分
  const auto result = std::memcmp(first1, first2, wzy_stl::min(len1, len2));
  // 若相等，则比较长度
  return result != 0 ? result < 0 : len1 < len2;
}

/*****************************************************************************************/
// mismatch
// 平行比较两个序列，找到第一处失配的元素，返回一对迭代器，分别指向两个序列中失配的元素
/*****************************************************************************************/
template <class InputIter1, class InputIter2>
wzy_stl::pair<InputIter1, InputIter2>
mismatch(InputIter1 first1, InputIter2 last1, InputIter2 first2)
{
  while(first1 != last1 && *first1 == *first2)
  {
    ++first1;
    ++first2;
  }
  return wzy_stl::pair<InputIter1, InputIter2>(first1, first2);
}

// 重载版本使用函数对象 comp 代替比较操作
template <class InputIter1, class InputIter2, class Compared>
wzy_stl::pair<InputIter1, InputIter2>
mismatch(InputIter1 first1, InputIter2 last1, InputIter2 first2, Compared comp)
{
  while(first1 != last1 && comp(*first1, *first2))
  {
    ++first1;
    ++first2;
  }
  return wzy_stl::pair<InputIter1, InputIter2>(first1, first2);
}

}

#endif