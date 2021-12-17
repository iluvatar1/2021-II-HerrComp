  /* mpi-V3.c */

  #include "mpi.h"
  #include <stdio.h>

  /* Problem parameters */
  double f(double x) {
    return x*x;
  }
  const int numberRects = 50;
  const double lowerLimit = 2.0;
  const double upperLimit = 5.0;


  int main(int argc, char **argv)
  {
    /* MPI Variables */
    int dest, noProcesses, processId, src, tag;
    MPI_Status status;

    /* problem variables */
    int i;
    double area, at, heigth, width, total, range, lower;

    /* MPI setup */
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);

    /* Adjust problem size for sub-process */
    range = (upperLimit - lowerLimit) / noProcesses;
    width = range / numberRects;
    lower = lowerLimit + range*processId;

    /* Calculate area for subproblem */
    area = 0.0;
    for (i = 0; i < numberRects; ++i) {
      at = lower + i*width + width/2.0;
      heigth = f(at);
      area = area + width*heigth;
    }

    /* Collect info and print results */
    tag = 0;
    if (0 == processId) { /* Master */
      total = area;
      for (src = 1; src < noProcesses; ++src) {
        MPI_Recv(&area, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, &status);
        total += area;
      }
      fprintf(stderr, "The area from %g to %g is : %25.16e\n", lowerLimit, upperLimit, total);
    }
    else { /* slaves only send */
      dest = 0;
      MPI_Send(&area, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }

    /* finish */
    MPI_Finalize();

    return 0;
  }
