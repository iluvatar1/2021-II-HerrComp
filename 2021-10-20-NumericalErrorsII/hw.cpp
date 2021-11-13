// calcular el sin(x = pi/3), usando la expansion matematica
// sin(x, N) = \sum_{n=1}^{N} (-1)^{n-1} x^{2n-1}/(2n-1)!

#include <iostream>
#include <cmath>

typedef double REAL; 

REAL mysin(REAL x, int N); // declaration

int main()
{
  std::cout.setf(std::ios::scientific);
  std::cout.precision(15);

  const REAL x = M_PI/3 + 20*M_PI;
  const REAL exact = std::sin(x);

  for(int NMAX = 1; NMAX <= 1000; NMAX++) {
    REAL myval = mysin(x, NMAX);
    REAL diff = std::fabs(myval - exact)/exact;
    std::cout << NMAX << "\t" << myval << "\t" << diff << "\n";
  }

  return 0;
}

REAL mysin(REAL x, int N) // implementation
{
  // an+1 = (-1) x^2 an /((2n+1)2n)
  REAL suma = 0;
  REAL an = x; 
  for(int n = 1; n <= N; n++) {
    suma += an;
    an = (-1)*x*x*an/((2*n+1)*2*n);
  }
  return suma;
}
