// calcular el sin(x = pi/3), usando la expansion matematica
// sin(x, N) = \sum_{n=1}^{N} (-1)^{n-1} x^{2n-1}/(2n-1)!

#include <iostream>
#include <cmath>

double mysin(double x, int N); // declaration

int main()
{
    std::cout.setf(std::ios::scientific);
    std::cout.precision(6);

    const double x = M_PI/3;
    const double exact = std::sin(x);

    for(int NMAX = 1; NMAX <= 1000; NMAX++) {
        double diff = std::fabs(mysin(x, NMAX) - exact)/exact;
        std::cout << NMAX << "\t" << diff << "\n";
    }

    return 0;
}

double mysin(double x, int N) // implementation
{
    return 0;
}
