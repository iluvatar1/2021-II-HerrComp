// Adapted to c++ from : https://www.gnu.org/software/gsl/doc/html/specfunc.html 
// compile as: g++ -std=c++17 name.cpp -lgsl -lgslcblas
#include <cstdio>
#include <cmath>
#include <gsl/gsl_sf_bessel.h>

int main (void)
{
    double x = 5.0;
    double expected = -0.17759677131433830434739701;
    double fromcmath = std::cyl_bessel_j(0, x);

    double y = gsl_sf_bessel_J0 (x);

    std::printf ("J0(5.0)     = %.18f\n", y);
    std::printf ("exact       = %.18f\n", expected);
    std::printf ("fromcmath   = %.18f\n", fromcmath);
    return 0;
}
