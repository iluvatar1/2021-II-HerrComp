#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>

int main(int argc , char **argv)
{
  int N = std::atoi(argv[1]);
  double * array = new double [N];

  #pragma omp parallel for 
  for(int ii = 0; ii < N; ii++){
    array[ii] = 2*std::sqrt(std::fabs(std::sin(ii)));
  }

  std::cout << array[N/2] << "\n";

  delete [] array;
  
  return 0;
}
