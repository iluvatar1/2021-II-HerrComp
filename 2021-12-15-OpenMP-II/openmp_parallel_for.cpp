#include <omp.h>
#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
    const int N = 80000000;
    int i;
    double *a = new double[N];

#pragma omp parallel for
    for(i = 0; i < N; i++) {
        a[i] = 2*i*std::sin(std::sqrt(i/56.7)) +
            std::cos(std::pow(i*i, 0.3));
    }

    std::cout << a[1] << "\n";

    delete [] a;
    return 0;
}
