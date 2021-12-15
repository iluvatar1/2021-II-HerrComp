#include <omp.h>
#include <iostream>
#include <cmath>

void fill_data(double *a, int size);
double average(double *a, int size);

int main(int argc, char *argv[]) {
    std::cout.precision(15); std::cout.setf(std::ios::scientific);

    const int N = 80000000;
    int i;
    double *a = new double[N];

    fill_data(a, N);
    std::cout << a[1] << std::endl;
    double avg = average(a, N);
    std::cout << avg << "\n";

    delete [] a;
    return 0;
}

void fill_data(double *a, int size)
{
    long int i;
#pragma omp parallel for
    for(i = 0; i < size; i++) {
        a[i] = 2*i*std::sin(std::sqrt(i/56.7)) +
            std::cos(std::pow(i*i, 0.3));
    }
}

double average(double *a, int size)
{
    double result = 0;
#pragma omp parallel for reduction(+:result)
    for(int ii = 0; ii < size; ++ii) {
        result += a[ii];
    }
    result /= size;
    return result;
}
