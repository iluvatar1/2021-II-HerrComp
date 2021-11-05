#include <iostream>
#include <cstdlib>
#include <cmath>

int main(void)
{
  const int N = 10;
  double data[N] = {0.0};
  double data2d[N][N] = {{0.0}};

  for(int ii = 0; ii < N; ++ii) {
    data[ii] = std::sin(ii);
  }

  for(int ii = 0; ii < N; ++ii) {
    for(int jj = 0; jj < N; ++jj) {
      data2d[ii][jj] = std::sin(ii)*std::cos(jj);
    } 
  }

  return EXIT_SUCCESS;
}
