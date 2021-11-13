#include <iostream>
#include "factorial.h"

int main(int argc, char **argv)
{
  const int N = std::atoi(argv[1]);
  
  std::cout << factorial(N) << std::endl;
    
  return 0;
}
