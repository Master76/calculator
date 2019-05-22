#include "stdafx.h"

#define MAX_SIZE 0xff

int main(int argc, char const* argv[])
{
  calculator* calc;
  int result;
  char formula[MAX_SIZE];

  while (!std::cin.eof()) {
    std::cin.getline(formula, MAX_SIZE);
    calc = new calculator(formula, strlen(formula));
    try {
      result = calc->result();
      std::cout << formula << "=" << result << std::endl;
    } catch (int errcode) {
      std::cout << "errcode=" << errcode << std::endl;
      return errcode;
    }
  }

  return 0;
}
