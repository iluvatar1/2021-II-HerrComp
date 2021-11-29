#include <iostream>
#include <omp.h>

int main(int argc, char *argv[]) {
    std::cout << "BEFORE\n";
#pragma omp parallel
    {
        std::cout << "Hola mundo\n";
    }
    std::cout << "AFTER\n";
    
    return 0;
}
