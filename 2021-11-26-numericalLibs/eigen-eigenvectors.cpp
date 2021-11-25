#include <iostream>
#include <eigen3/Eigen/Dense>

int main()
{
    Eigen::Matrix2d A;
    A << 1, 2, 2, 3;
    std::cout << "Here is the matrix A:\n" << A << std::endl;
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> eigensolver(A);
    std::cout << "The eigenvalues of A are:\n" << eigensolver.eigenvalues() << std::endl;
    std::cout << "Here's a matrix whose columns are eigenvectors of A \n"
              << "corresponding to these eigenvalues:\n"
              << eigensolver.eigenvectors() << std::endl;
}
