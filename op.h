#pragma once

typedef int (*unaryOp)(int);
typedef int (*binaryOp)(int, int);

#define VERBOSE

#ifdef VERBOSE
#include <iostream>
#endif

namespace operators {
// unary operators
inline int unaryAdd(int val)
{
#ifdef VERBOSE
  std::cout << '+' << val << std::endl;
#endif
  return val;
}
inline int unarySub(int val)
{
#ifdef VERBOSE
  std::cout << '-' << val << std::endl;
#endif
  return -val;
}

// binary operators
inline int binaryAdd(int left, int right)
{
#ifdef VERBOSE
  std::cout << left << '+' << right << "=" << left + right << std::endl;
#endif
  return left + right;
}
inline int binarySub(int left, int right)
{
#ifdef VERBOSE
  std::cout << left << '-' << right << "=" << left - right << std::endl;
#endif
  return left - right;
}
inline int binaryMul(int left, int right)
{
#ifdef VERBOSE
  std::cout << left << '*' << right << "=" << left * right << std::endl;
#endif
  return left * right;
}
inline int binaryDiv(int left, int right)
{
#ifdef VERBOSE
  std::cout << left << '/' << right << "=" << left / right << std::endl;
#endif
  return left / right;
}
}
