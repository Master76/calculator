#pragma once
#include "cstdlib"
#include "expr.h"
#include "op.h"
#include "status.h"

#define MALFORMED 0xcc01
#define NOT_SUPPORTED 0xcc03

#define INT_MAXLENGTH 10

class calculator
{
private:
  int* res;
  char* formula;
  int length;
  expr* exprRoot;

private:
  expr* parse(const int start, const int end);
  expr* parse(const int start, const int end, int expected, expr* node);
  char peek(const int& pos);
  int integer(int& pos);
  int findBlock(const int start, const int end);

public:
  calculator(char* formula, int length);
  ~calculator();
  int result();
};
