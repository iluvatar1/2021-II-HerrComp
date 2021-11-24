/* Shows a way to do operations that require a specific order (e.g.,
 * transpositions) while avoiding cache misses. */

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <Eigen/Dense>

#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

bool verify_transpose(float ** m1, float ** m2, int n);
template <class T, class U>
bool verify_transpose(T & m1, U & m2, int n);

int main(){
    const int n = 12000;
    const int csize = 8;
    float **a, **b;
    clock_t cputime1, cputime2;
    int i,j,k,ii,jj,kk;

    // Allocating memory for array/matrix
    cputime1 = clock();
    a = new float * [n];
    for (i=0; i<n; i++){
        a[i] = new float [n];
    }
    b = new float * [n];
    for (i=0; i<n; i++){
        b[i] = new float[n];
    }
    // eigen matrices
    Eigen::MatrixXf M2 = Eigen::MatrixXf::Constant(n, n, 0.0);
    cputime2 = clock() - cputime1;
    std::printf("Time for memory allocation: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);

    // Filling matrices with zeros
    cputime1 = clock();
    for(i=0; i<n; ++i)
        for (j=0; j<n; ++j) {
            a[i][j] = 2.3*i + j + 0.1;
        }
    for(i=0; i<n; ++i)
        for (j=0; j<n; ++j) {
            b[i][j] = -2.3*i + 1.8*j + 0.1;
            M2(i, j) = 2.3*i + j + 0.1;
        }
    cputime2 = clock() - cputime1;
    std::printf("Time for filling: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);

    // Direct (inefficient) transposition
    cputime1 = clock();
    for (i=0; i<n; ++i)
        for (j=0; j<n; ++j)
            a[i][j] = b[j][i];
    cputime2 = clock() - cputime1;
    std::printf("Time for direct transposition: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);
    assert(verify_transpose(a, b, n));

    // Transposition using cache-blocking
    cputime1 = clock();
    for (ii=0; ii<n; ii+=csize)
        for (jj=0; jj<n; jj+=csize)
            for (i=ii; i<min(n,ii+csize-1); ++i)
                for (j=jj; j<min(n,jj+csize-1); ++j)
                    a[i][j] = b[j][i];
    assert(verify_transpose(a, b, n));
    cputime2 = clock() - cputime1;
    std::printf("Time for blocked transposition: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);

    // eigen
    cputime1 = clock();
    //M1.noalias() = M2.transpose();
    auto M1{M2.transpose()};
    assert(verify_transpose(M1, M2, n));
    cputime2 = clock() - cputime1;
    std::printf("Time for transposition with eigen: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);
    cputime1 = clock();
    auto M3 = M2.transpose();
    cputime2 = clock() - cputime1;
    std::printf("Time for transposition with copy in eigen: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);
    cputime1 = clock();
    Eigen::MatrixXf M4 = M2.transpose();
    cputime2 = clock() - cputime1;
    std::printf("Time for transposition with full copy in eigen: %f\n", ((double)cputime2)/CLOCKS_PER_SEC);
    assert(verify_transpose(M1, M2, n));
    assert(verify_transpose(M3, M2, n));
    assert(verify_transpose(M4, M2, n));

    // use data
    M1(n/4, n/2) = 0.9876;
    M2(n/2, n/4)= 9.88;
    std::cout << a[n/2][n/2] << std::endl;
    std::cout << b[n/2][n/2] << std::endl;
    std::cout << M1(n/2,n/3) << std::endl;
    std::cout << M2(n/3,n/2) << std::endl;
    std::cout << M3(n/2,n/3) << std::endl;

    return 0;
}

bool verify_transpose(float ** m1, float ** m2, int n)
{
    for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            if (m1[ii][jj] != m2[jj][ii]) {
                return false;
            }
        }
    }
    return true;
}

template <class T, class U>
bool verify_transpose(T & m1, U & m2, int n)
{
    for (int ii = 0; ii < n; ++ii) {
        for (int jj = 0; jj < n; ++jj) {
            if (m1(ii, jj) != m2(jj, ii)) {
                return false;
            }
        }
    }
    return true;

}
