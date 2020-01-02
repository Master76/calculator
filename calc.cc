#include "calc.h"
#include <cstdlib>

#ifdef VERBOSE
#include <iostream>
#endif

inline bool isDigit(char chr)
{
  return chr >= '0' && chr <= '9';
}

calculator::calculator(char* formula, int length)
  : formula(formula)
  , length(length)
  , exprRoot(nullptr)
  , res(nullptr)
{}

calculator::~calculator()
{
  formula = nullptr;
  res = nullptr;
  exprRoot = nullptr;
}

expr* calculator::parse(
  const int start, const int end, int expected, expr* node)
{
#ifdef VERBOSE
  std::cout << "parse: ";
  for (int i = start; i < end; i++) {
    std::cout << formula[i];
  }
  std::cout << std::endl;
#endif
  char chr;
  int pos = start;

  void* op = nullptr;
  status opType = INVALID;

  while (pos < end) {
    do {
      chr = peek(pos);
    } while (chr == ' ' && ++pos < end);

    if (expected & EXPRESSION) {
      expr* tNode;
      if (chr == '(') {
        int nEnd = findBlock(pos + 1, end);
        if (nEnd == -1) throw MALFORMED;
        tNode = parse(pos + 1, nEnd - 1);
        pos = nEnd;
      } else if (isDigit(chr)) {
        tNode = new constant(integer(pos));
      } else
        throw MALFORMED;

      if (opType == INVALID) {
        node = tNode;
      } else if (opType == UNARY_OP) {
        unary* uNode = new unary((unaryOp)op);
        uNode->val = tNode;
        node = uNode;
      } else if (opType == BINARY_OP1) {
        binary* bNode = new binary((binaryOp)op);
        bNode->left = node;
        bNode->right = tNode;
        node = bNode;
      } else if (opType == BINARY_OP) {
        binary* bNode = new binary((binaryOp)op);
        bNode->left = node;
        bNode->right = pos < end ? parse(pos, end, BINARY_OP, tNode) : tNode;
        return bNode;
      }
      opType = INVALID;
      op = nullptr;
      expected = BINARY_OP;
      continue;
    }
    pos++;
    if (expected & UNARY_OP) {
      switch (chr) {
        case '+':
          op = (void*)operators::unaryAdd;
          opType = UNARY_OP;
          expected = EXPRESSION;
          continue;
        case '-':
          op = (void*)operators::unarySub;
          opType = UNARY_OP;
          expected = EXPRESSION;
          continue;
        default:
          throw MALFORMED;
      }
    }
    if (expected & BINARY_OP) {
#ifdef VERBOSE
      std::cout << "BINARY_OP: " << chr << std::endl;
#endif
      switch (chr) {
        case '+':
          op = (void*)operators::binaryAdd;
          opType = BINARY_OP;
          expected = EXPRESSION;
          continue;
        case '-':
          op = (void*)operators::binarySub;
          opType = BINARY_OP;
          expected = EXPRESSION;
          continue;
        case '*':
          op = (void*)operators::binaryMul;
          opType = BINARY_OP1;
          expected = EXPRESSION;
          continue;
        case '/':
          op = (void*)operators::binaryDiv;
          opType = BINARY_OP1;
          expected = EXPRESSION;
          continue;
      }
    }
  }

  return node;
}

expr* calculator::parse(const int start, const int end)
{
  return parse(start, end, EXPRESSION | UNARY_OP, nullptr);
}

char calculator::peek(const int& pos)
{
  if (pos >= length) return '\0';
  return formula[pos];
}

int calculator::integer(int& pos)
{
  char chr, intstr[INT_MAXLENGTH + 1];
  int cread = 0;
  while (chr = peek(pos + cread)) {
    if (isDigit(chr)) {
      if (cread > INT_MAXLENGTH) throw NOT_SUPPORTED;
      intstr[cread++] = chr;
    } else
      break;
  }
  intstr[cread] = '\0';
  pos += cread;
#ifdef VERBOSE
  std::cout << "integer: return=" << intstr << std::endl;
#endif
  return atoi(intstr);
}

int calculator::findBlock(const int start, const int end)
{
  char chr;
  int pos = start;
  int c = 1;
  while (pos < end) {
    chr = peek(pos++);
    switch (chr) {
      case '\0':
        return -1;
      case '(':
        c++;
        break;
      case ')':
        if (--c == 0) return pos;
        break;
      default:
        break;
    }
  }
  return -1;
}

int calculator::result()
{
  if (res != nullptr) return *res;
  int val, pos = 0;
  exprRoot = parse(pos, length);
#ifdef VERBOSE
  std::cout << "calculating result:" << std::endl;
#endif
  val = exprRoot->value();
  res = &val;
  return val;
}
