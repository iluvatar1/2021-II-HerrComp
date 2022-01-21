#include "mpi.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <numeric>

void send_data_collective(int size, int pid, int np);

int main(int argc, char **argv)
{
  int np, pid;

  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  const int SIZE = std::atoi(argv[1]);
  send_data_collective(SIZE, pid, np);

  MPI_Finalize();

  return 0;
}

void send_data_collective(int size, int pid, int np)
{
  // create data buffer (all processes)
  double * data = new double [size];
  if (0 == pid) {
    std::iota(data, data+size, 0.0); // llena como 0 1 2 3 4 
  }
  // send data to all processes
  int root = 0;
  double start = MPI_Wtime();
  MPI_Bcast(&data[0], size, MPI_DOUBLE, root, MPI_COMM_WORLD);
  double end = MPI_Wtime();
  // print size, time, bw in root
  if (0 == pid) {
    int datasize = sizeof(double)*size;
    std::cout << datasize << "\t" << (end-start) << "\t"
              << datasize/(end-start)/1.0e6 << "\n";
  }
  delete [] data;
}
