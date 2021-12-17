  #include "mpi.h"
  #include <cstdio>

  int main(int argc, char **argv)
  {
    int processId;                 /* rank of process */
    int noProcesses;               /* number of processes */

    MPI_Init(&argc, &argv);                   /* Mandatory */
    MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);

    fprintf(stderr, "Hello from process %d of %d\n", processId, noProcesses);

    MPI_Finalize();                       /* Mandatory */

    return 0;
  }
