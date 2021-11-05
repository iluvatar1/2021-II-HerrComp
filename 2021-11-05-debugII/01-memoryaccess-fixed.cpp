#include <iostream>

void leak(double * ptr, int N) ;

int main(void) {
  //double x[10], y[5]; // imprime raro
  double y[5] = {0}, x[10] = {0}; // imprime 1
  for (int ii = 0; ii < 5; ++ii) {
    y[ii] *= 1.7;
  }
  std::cout << y[0] << std::endl;
  std::cout << y[4] << std::endl;

  for (int ii = 0; ii < 10; ++ii) {
    x[ii] = -(ii + 1);
  }

  double z = x[9];
  std::cout << z << std::endl;

  double * localptr = nullptr;
  leak(localptr, 100);

  return 0;
}

void leak(double * ptr, int N)
{
  int ii = 0;
  ptr = new double[N];
  // algo
  ptr[1] = ptr[ii]+9;
  //free memory
  delete [] ptr;
}
////x[10] -> &x[0] + 10
// [ | | | | ][ | | | | | | | | | ]XXXX x[10] y[5]  x[10] memoria por fuera
// [ | | | | | | | | | ][X| | | | ] y[5] x[10]      x[10] = y[0]
