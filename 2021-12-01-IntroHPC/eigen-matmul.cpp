#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <eigen3/Eigen/Dense>


void multiply(const int size, double & wtime, double & ctime); // store time spent multiplying
void stats(const int size, const int reps,
           double & mean_wtime, double & sigma_wtime,
           double & mean_ctime, double & sigma_ctime);

int main(int argc, char ** argv)
{
  const int M = atoi(argv[1]); // Matrix size
  const int R = atoi(argv[2]); // Repetitions

  double mean_wtime, sigma_wtime;
  double mean_ctime, sigma_ctime;
  stats(M, R, mean_wtime, sigma_wtime, mean_ctime, sigma_ctime);
  std::cout << M
            << "\t" << mean_wtime << "\t" << sigma_wtime
            << "\t" << mean_ctime << "\t" << sigma_ctime
            << std::endl;

  return 0;
}
void stats(const int size, const int reps,
           double & mean_wtime, double & sigma_wtime,
           double & mean_ctime, double & sigma_ctime)
{
  double wsum = 0, wsum2 = 0, csum = 0, csum2 = 0;
  double wtime = 0, ctime = 0;
  for (int rep = 0; rep < reps; ++rep) {
    srand(rep+1); // change seed for each repetition
    multiply(size, wtime, ctime);
    wsum  += wtime;
    wsum2 += wtime*wtime;
    csum  += ctime;
    csum2 += ctime*ctime;
  }
  mean_wtime = wsum/reps;
  sigma_wtime = std::sqrt(reps*(wsum2/reps - mean_wtime*mean_wtime)/(reps-1));
  mean_ctime = csum/reps;
  sigma_ctime = std::sqrt(reps*(csum2/reps - mean_ctime*mean_ctime)/(reps-1));
}


void multiply(const int size, double & wtime, double & ctime)
{
  // create matrices
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(size, size);

  auto start = std::chrono::system_clock::now(); // measures wall time
  std::clock_t c1 = std::clock(); // measures cpu time
  auto C{A*B}; // MULTIPLY
  double tmp = C(0, 0); // use the matrix to make eigen compute it
  auto end = std::chrono::system_clock::now(); // wall time
  std::clock_t c2 = std::clock(); // cpu time

  std::clog << tmp << std::endl; // use the matrix to make eigen compute it

  ctime = 1.0*(c2-c1)/CLOCKS_PER_SEC;
  std::chrono::duration<double> elapsed_seconds = end-start;
  wtime = elapsed_seconds.count();
}
