#include "mpi.h"
#include <iostream>

int main(int argc, char **argv)
{
  /* MPI Variables */
  int dest, np, pid, src, tag, buffer;
  MPI_Status status;

  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  tag = 0;
  if (0 == pid) { /* Master */
    MPI_Recv(&buffer, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &status);
    MPI_Send(&pid, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
    std::cout << buffer << std::endl;
  }
  else { /* slaves only send */
    dest = 0;
    MPI_Recv(&buffer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    buffer += 99;
    MPI_Send(&buffer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
  }

  /* finish */
  MPI_Finalize();

  return 0;
}
