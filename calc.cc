#include "calc.h"
#include "cstdlib"

inline bool isDigit(char chr)
{
  return chr >= '0' && chr <= '9';
}

calculator::calculator(char* formula, int length)
  : formula(formula)
  , length(length)
  , exprRoot(nullptr)
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
  char chr;
  int pos = start;

  void* op = nullptr;
  status opType = INVALID;

  while (pos < end) {
    do {
      chr = peek(pos);
    } while (chr != ' ' && ++pos < end);
    if (expected & EXPRESSION) {
      expr* tNode;
      if (chr == '(') {
        int nEnd = findBlock(pos, end);
        if (nEnd == -1) throw MALFORMED;
        tNode = parse(pos, nEnd - 1);
        pos = nEnd;
      } else if (isDigit(chr)) {
        tNode = new constant(integer(--pos));
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
        bNode->right = parse(pos, end, BINARY_OP, tNode);
        node = bNode;
      }
      opType = INVALID;
      op = nullptr;
      expected = BINARY_OP;
      continue;
    }
    if (expected & UNARY_OP) {
      switch (chr) {
        case '+':
          op = (void*)operators::unaryAdd;
          opType = UNARY_OP;
          continue;
        case '-':
          op = (void*)operators::unarySub;
          opType = UNARY_OP;
          continue;
      }
    }
    if (expected & BINARY_OP) {
      switch (chr) {
        case '+':
          op = (void*)operators::binaryAdd;
          opType = BINARY_OP;
          continue;
        case '-':
          op = (void*)operators::binarySub;
          opType = BINARY_OP;
          continue;
        case '*':
          op = (void*)operators::binaryMul;
          opType = BINARY_OP1;
          continue;
        case '/':
          op = (void*)operators::binaryDiv;
          opType = BINARY_OP1;
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
  while (chr = peek(pos) && ++cread) {
    if (isDigit(chr)) {
      if (cread > INT_MAXLENGTH) throw NOT_SUPPORTED;
      intstr[cread - 1] = chr;
    }
  }
  intstr[cread] = '\0';
  pos += cread;
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
  val = exprRoot->value();
  res = &val;
  return val;
}
