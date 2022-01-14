#include "mpi.h"
#include <cstdio>

int main(int argc, char **argv)
{
  /* MPI Variables */
  int dest, noProcesses, processId, src, tag;
  MPI_Status status;

  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &processId);

  /* Collect info and print results */
  tag = 0;
  if (0 == processId) { /* Master */
    MPI_Recv(&area, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, &status);
    //fprintf(stderr, "The area from %g to %g is : %25.16e\n", lowerLimit, upperLimit, total);
  }
  else { /* slaves only send */
    dest = 0;
    MPI_Send(&area, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }

  /* finish */
  MPI_Finalize();

  return 0;
}
