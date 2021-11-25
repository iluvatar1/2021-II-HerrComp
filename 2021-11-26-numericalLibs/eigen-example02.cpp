#include <iostream>
#include <eigen3/Eigen/Dense>

int main()
{
    const int N = 3;
    srand(10);
    Eigen::MatrixXd m = Eigen::MatrixXd::Random(N, N);
    m = (m + Eigen::MatrixXd::Constant(N, N, 1.2)) * 50;
    std::cout << "m =" << std::endl << m << std::endl;
    Eigen::VectorXd v(N);
    v << 1, 2, 3;
    std::cout << "m * v =" << std::endl << m * v << std::endl;
}
