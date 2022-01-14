#include "mpi.h"
#include <iostream>
#include <cstdlib>

void bandwidth(int reps, int size, int pid, int np);

int main(int argc, char **argv)
{
  /* MPI Variables */
  int np, pid;

  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  const int REPS = std::atoi(argv[1]);  
  const int SIZE = std::atoi(argv[2]);  
  bandwidth(REPS, SIZE, pid, np);

  /* finish */
  MPI_Finalize();

  return 0;
}

void bandwidth(int reps, int size, int pid, int np)
{
  MPI_Status status;
  int tag = 0;
  double * buffer = new double [size]{1};
  for(int ii = 0; ii < reps; ++ii) {
    if (0 == pid) { /* Master */
      double tstart = MPI_Wtime();
      MPI_Send(&buffer[0], size, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD);
      MPI_Recv(&buffer[0], size, MPI_DOUBLE, 1, tag, MPI_COMM_WORLD, &status);
      double tend = MPI_Wtime();
      double total_time = tend - tstart;
      std::cout << size*sizeof(double) << "\t" << total_time << "\t" << size*sizeof(double)/total_time/1.0e6 << std::endl;
    }
    else { /* slaves only send */
      MPI_Recv(&buffer[0], size, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
      MPI_Send(&buffer[0], size, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    }
  }
}
