#include "calc.h"
#include <cstring>
#include <iostream>

#define MAX_SIZE 0xff

int main(void)
{
  calculator* calc;
  char formula[MAX_SIZE];

  while (!std::cin.eof()) {
    std::cin.getline(formula, MAX_SIZE);
    calc = new calculator(formula, strlen(formula));
    try {
      std::cout << calc->result() << std::endl;
    } catch (int errcode) {
      return errcode;
    }
  }

  return 0;
}
