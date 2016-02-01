#ifndef _PLACEHOLDER_H_
#define _PLACEHOLDER_H_

#include <utility>
#include <functional>

struct Placeholder{};

Placeholder _;

template<typename _V, typename _Op>
struct Expression
{
  Expression(const _V& v, _Op&& op)
  : value(v), operation(op)
  {}
  _V value;
  _Op operation;
  template<typename _T>
  bool operator()(const _T& v)
  {
    return operation(v, value);
  }
};

template<typename _T>
Expression<_T, std::equal_to<_T>> operator==(const Placeholder&, const _T& value)
{
  return Expression<_T, std::equal_to<_T>>(value, std::equal_to<_T>());
}

template<typename _T>
Expression<_T, std::not_equal_to<_T>> operator!=(const Placeholder&, const _T& value)
{
  return Expression<_T, std::not_equal_to<_T>>(value, std::equal_to<_T>());
}

template<typename _T>
Expression<_T, std::less<_T>> operator<(const Placeholder&, const _T& value)
{
  return Expression<_T, std::less<_T>>(value, std::less<_T>());
}

template<typename _T>
Expression<_T, std::less_equal<_T>> operator<=(const Placeholder&, const _T& value)
{
  return Expression<_T, std::less_equal<_T>>(value, std::less_equal<_T>());
}

template<typename _T>
Expression<_T, std::greater<_T>> operator>(const Placeholder&, const _T& value)
{
  return Expression<_T, std::greater<_T>>(value, std::greater<_T>());
}

template<typename _T>
Expression<_T, std::greater_equal<_T>> operator>=(const Placeholder&, const _T& value)
{
  return Expression<_T, std::greater_equal<_T>>(value, std::greater_equal<_T>());
}

#endif // _PLACEHOLDER_H_
