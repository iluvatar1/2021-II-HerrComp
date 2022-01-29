#include <iostream>
#include <vector>
#include <cmath>
#include "mpi.h"

// constants
// const double DELTA = 0.05;
// const double L = 1.479;
// const int N = int(L/DELTA)+1;
// const int STEPS = 200;

typedef std::vector<double> Matrix; // alias

void initial_conditions(Matrix & m, int nrows, int ncols);
void boundary_conditions(Matrix & m, int nrows, int ncols);
void evolve(Matrix & m, int nrows, int ncols);
void print(const Matrix & m, double delta, int nrows, int ncols);
void init_gnuplot(void);
void plot_gnuplot(const Matrix & m, double delta, int nrows, int ncols);


int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int pid, np;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  const int STEPS = std::atoi(argv[1]);
  const double L = std::atof(argv[2]);
  const double DELTA = std::atof(argv[3]);
  const int N = int(L/DELTA) + 1;

  // problem partition
  int NCOLS = N, NROWS = N/np;
  Matrix data(NROWS*(NCOLS + 2)); // include ghosts cells

  /*
  // Serial version
  Matrix data(N*N);
  initial_conditions(data, N, N, ...);
  print_screen(...);
  boundary_conditions(data, N, N, ...);
  init_gnuplot();
  for (int istep = 0; istep < STEPS; ++istep) {
    evolve(data, N, N);
    plot_gnuplot(data, DELTA, N, N);
  }
  */

  MPI_Finalize();
  return 0;
}
/////////////////////////////////////////////////////
// SERIAL VERSIONS

void initial_conditions(Matrix & m, int nrows, int ncols)
{
  for(int ii=0; ii<nrows; ++ii) {
    for(int jj=0; jj<ncols; ++jj) {
      m[ii*ncols + jj] = 1.0;
    }
  }
}
void boundary_conditions(Matrix & m, int nrows, int ncols)
{
  int ii = 0, jj = 0;

  ii = 0;
  for (jj = 0; jj < ncols; ++jj)
    m[ii*ncols + jj] = 100;

  ii = nrows-1;
  for (jj = 0; jj < ncols; ++jj)
    m[ii*ncols + jj] = 0;

  jj = 0;
  for (ii = 1; ii < nrows-1; ++ii)
    m[ii*ncols + jj] = 0;

  jj = ncols-1;
  for (ii = 1; ii < nrows-1; ++ii)
    m[ii*ncols + jj] = 0;
}

void evolve(Matrix & m, int nrows, int ncols)
{
  for(int ii=0; ii<nrows; ++ii) {
    for(int jj=0; jj<ncols; ++jj) {
      // check if boundary
      if(ii == 0) continue;
      if(ii == nrows-1) continue;
      if(jj == 0) continue;
      if(jj == ncols-1) continue;
      // evolve non boundary
      m[ii*ncols+jj] = (m[(ii+1)*ncols + jj] +
                    m[(ii-1)*ncols + jj] +
                    m[ii*ncols + jj + 1] +
                    m[ii*ncols + jj - 1] )/4.0;
    }
  }
}

void print(const Matrix & m, double delta, int nrows, int ncols)
{
  for(int ii=0; ii<nrows; ++ii) {
    for(int jj=0; jj<ncols; ++jj) {
      std::cout << ii*delta << " " << jj*delta << " " <<  m[ii*ncols + jj] << "\n";
    }
    std::cout << "\n";
  }  
}

void init_gnuplot(void)
{
  std::cout << "set contour " << std::endl;
  //std::cout << "set terminal gif animate " << std::endl;
  //std::cout << "set out 'anim.gif' " << std::endl;
}

void plot_gnuplot(const Matrix & m, double delta, int nrows, int ncols)
{
  std::cout << "splot '-' w pm3d " << std::endl;
  print(m, delta, nrows, ncols);
  std::cout << "e" << std::endl;
}
