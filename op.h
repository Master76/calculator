#pragma once

typedef int (*unaryOp)(int);
typedef int (*binaryOp)(int, int);

namespace operators {
// unary operators
inline int unaryAdd(int val)
{
  return val;
}
inline int unarySub(int val)
{
  return -val;
}

// binary operators
inline int binaryAdd(int left, int right)
{
  return left + right;
}
inline int binarySub(int left, int right)
{
  return left - right;
}
inline int binaryMul(int left, int right)
{
  return left * right;
}
inline int binaryDiv(int left, int right)
{
  return left / right;
}
}
