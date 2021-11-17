#include <iostream>
#include <cstdlib>
#include <cassert>

// TODO : add test

void test_factorial(void);
int factorial(int n);

int main(int argc, char **argv)
{
  test_factorial();
  
  const int N = std::atoi(argv[1]);
  
  std::cout << factorial(N) << std::endl;
    
  return 0;
}


int factorial(int number)
{
  if (0 == number) return 1;
  return number <= 1 ? number : factorial(number-1)*number;
}

void test_factorial(void)
{
  assert(factorial(0) == 1);
  assert(factorial(2) == 2);
  assert(factorial(10) == 3628800);
}
