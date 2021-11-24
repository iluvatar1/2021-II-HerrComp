#include <iostream>

int main(void)
{
    const int M = 7000;
    const int N = 500;

    double **data = nullptr;
    data = new double *[M];
    for (int ii = 0; ii < M; ++ii){
        data[ii] = new double [N];
    }

    std::cout << data[M/2][N/2] << std::endl;

    for (int ii = 0; ii < M; ++ii){
        delete [] data[ii];
    }
    delete [] data;

    return 0;
}
