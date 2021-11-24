#include <iostream>

int main(void)
{
    const int M = 700;
    const int N = 500;
    double data[M][N] = {{0.0}};

    std::cout << data[M/2][N/2] << std::endl;

    return 0;
}
