#include "stdafx.h"

#define MAX_SIZE 0xff

int main(int argc, char const* argv[])
{
  calculator* calc;
  std::ofstream out;
  int result;
  char formula[MAX_SIZE];

  if (argc != 3) return -1;

  std::strcpy(formula, argv[1]);
  out = std::ofstream(argv[2]);
  std::cout.rdbuf(out.rdbuf());

  calc = new calculator(formula, strlen(formula));
  try {
    result = calc->result();    
    std::cout << formula << "=" << result << std::endl;
  } catch (int errcode) {
    std::cout << "errcode=" << errcode << std::endl;
    return errcode;
  }

  return 0;
}
