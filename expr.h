#pragma once
#include "op.h"

class expr
{
public:
  virtual int value() = 0;
};

class constant : public virtual expr
{
private:
  int val;

public:
  constant(int val) { this->val = val; }
  int value() override { return val; }
};

class unary : public virtual expr
{
private:
  unaryOp op;

public:
  expr* val;

public:
  unary(unaryOp op)
    : op(op)
    , val(nullptr)
  {}
  int value() { return op(val->value()); }
};

class binary : public virtual expr
{
private:
  binaryOp op;

public:
  expr* left;
  expr* right;

public:
  binary(binaryOp op)
    : op(op)
    , left(nullptr)
    , right(nullptr)
  {}
  int value() { return op(left->value(), right->value()); }
};
