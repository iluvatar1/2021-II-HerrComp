#include "factorial.h"

long factorial(long number)
{
  if (number == 0) return 1;
  return number <= 1 ? number : factorial(number-1)*number;
}

void test_factorial(void)
{
  assert(factorial(0) == 1);
  assert(factorial(2) == 2);
  assert(factorial(10) == 3628800);
}

