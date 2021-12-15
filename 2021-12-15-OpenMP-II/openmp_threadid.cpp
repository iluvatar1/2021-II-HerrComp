#include <cstdio>
#include <omp.h>

int main(void)
{
    double x = 9.0;

    int nth = omp_get_num_threads();
    int thid = omp_get_thread_num();
    std::printf("Hello world from thid: %d, out of %d .\n",
                thid, nth);

//#pragma omp parallel num_threads(4)
#pragma omp parallel
    {// se generan los threads
        int nth = omp_get_num_threads();
        int thid = omp_get_thread_num();
        std::printf("Hello world from thid: %d, out of %d .\n",
                    thid, nth);
    } // mueren los threads

    return 0;
}
