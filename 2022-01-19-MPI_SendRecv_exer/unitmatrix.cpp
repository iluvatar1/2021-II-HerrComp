#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include "mpi.h"

typedef std::vector<double> data_t; // alias
//typedef double * data_t; // alias

void fill_matrix(data_t & data, int nrows, int ncols, int pid, int np);
void print_matrix(const data_t & data, int nrows, int ncols, int pid, int np);
void print_slab(const data_t & data, int nrows, int ncols);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv); /* Mandatory */

  int pid;                 /* rank of process */
  int np;                 /* number of processes */

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  int N = std::atoi(argv[1]);
  int Nlocal = N/np;

  data_t data; data.resize(Nlocal*N);
  std::fill(data.begin(), data.end(), 0.0);
  //data_t data = new double [Nlocal*N] {0.0};

  fill_matrix(data, Nlocal, N, pid, np);
  print_matrix(data, Nlocal, N, pid, np);

  //delete [] data; data = nullptr;

  MPI_Finalize(); /* Mandatory */

  return 0;
}


void fill_matrix(data_t & data, int nrows, int ncols, int pid, int np)
{
  for(int ilocal = 0; ilocal < nrows; ++ilocal) {
    int jlocal = nrows*pid + ilocal;
    data[ilocal*ncols + jlocal] = 1.0;
  }
}

void print_matrix(const data_t & data, int nrows, int ncols, int pid, int np)
{
  int tag = 0;
  if (0 == pid) { // master: receives and print
    // print local matrix
    print_slab(data, nrows, ncols);
    // create a buffer to receive data
    data_t buffer(nrows*ncols);
    //data_t buffer = new double [nrows*ncols] {0.0};
    // receive and print from each worker
    for(int src = 1; src < np; ++src) {
      MPI_Recv(&buffer[0], nrows*ncols, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      print_slab(buffer, nrows, ncols);
    }
    //delete [] buffer; buffer = nullptr;
  } else { // workers send
    MPI_Send(&data[0], nrows*ncols, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
  }
}

void print_slab(const data_t & data, int nrows, int ncols)
{
  for(int ilocal = 0; ilocal < nrows; ++ilocal) {
    for(int jlocal = 0; jlocal < ncols; ++jlocal) {
      std::cout << data[ilocal*ncols + jlocal] << " ";
    }
    std::cout << "\n";
  }
}
