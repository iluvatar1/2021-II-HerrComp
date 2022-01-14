#include "mpi.h"
#include <iostream>
#include <cstdlib>

void pingpong(int reps, int pid, int np);

int main(int argc, char **argv)
{
  /* MPI Variables */
  int np, pid;

  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  const int REPS = std::atoi(argv[1]);  
  pingpong(REPS, pid, np);

  /* finish */
  MPI_Finalize();

  return 0;
}

void pingpong(int reps, int pid, int np)
{
  MPI_Status status;
  int tag = 0, buffer = pid;
  for(int ii = 0; ii < reps; ++ii) {
    if (0 == pid) { /* Master */
      MPI_Send(&buffer, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
      MPI_Recv(&buffer, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
      std::cout << buffer << std::endl;
    }
    else { /* slaves only send */
      MPI_Recv(&buffer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
      buffer += 99;
      MPI_Send(&buffer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
  }
}
