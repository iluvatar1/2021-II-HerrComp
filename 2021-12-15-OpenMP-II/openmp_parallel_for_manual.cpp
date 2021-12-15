#include <omp.h>
#include <iostream>
#include <cmath>

int main(int argc, char *argv[]) {
    const int N = 80000000;
    int i;
    double *a = new double[N];

#pragma omp parallel private(i)
    {
        int thid = omp_get_thread_num();
        int nth = omp_get_num_threads();
        int localsize = N/nth;
        int iimin = thid*localsize;
        int iimax = iimin + localsize;
        for(i = iimin; i < iimax; i++) {
            a[i] = 2*i*std::sin(std::sqrt(i/56.7)) +
                std::cos(std::pow(i*i, 0.3));
        }
    }

    std::cout << a[1] << "\n";

    delete [] a;
    return 0;
}
