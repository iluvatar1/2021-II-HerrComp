// Este programa compara la suma harmonica realizada
// de dos formas diferentes para mostrar las
// diferencias computacionales

#include <iostream>

typedef float REAL;
REAL sumup(int N);
REAL sumdown(int N);

int main(void)
{

    return 0;
}

REAL sumup(int N)
{
    REAL suma = 0;
    for(int ii = 1; ii <= N; ++ii) {
        suma += 1/ii;
    }
    return suma;
}

REAL sumdown(int N)
{
    REAL suma = 0;
    for(int ii = N; ii >= 1; --ii) {
        suma += 1/ii;
    }
    return suma;
}
