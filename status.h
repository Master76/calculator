#pragma once

enum status
{
  INVALID = 0,
  EXPRESSION = 1 << 2,
  UNARY_OP = 1 << 3,
  BINARY_OP = 1 << 4,
  BINARY_OP1 = BINARY_OP + 1
};
