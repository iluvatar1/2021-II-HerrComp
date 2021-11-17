#include <iostream>
#include <cstdlib>

// TODO : add test

int factorial(int n);

int main(int argc, char **argv)
{
    const int N = std::atoi(argv[1]);

    std::cout << factorial(N) << std::endl;

    return 0;
}


int factorial(int number)
{
    return number <= 1 ? number : factorial(number-1)*number;
}
