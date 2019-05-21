#pragma once

typedef int (*unaryOp)(int);
typedef int (*binaryOp)(int, int);

namespace operators {
// unary operators
int unaryAdd(int val)
{
  return val;
}
int unarySub(int val)
{
  return -val;
}

// binary operators
int binaryAdd(int left, int right)
{
  return left + right;
}
int binarySub(int left, int right)
{
  return left - right;
}
int binaryMul(int left, int right)
{
  return left * right;
}
int binaryDiv(int left, int right)
{
  return left / right;
}
}
