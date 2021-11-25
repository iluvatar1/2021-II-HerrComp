#include <iostream>
#include <eigen3/Eigen/Dense>

int main(void)
{
    Eigen::MatrixXd m(2, 2);
    m(0, 1) = -9.877;
    std::cout << m << std::endl;

    return 0;
}
