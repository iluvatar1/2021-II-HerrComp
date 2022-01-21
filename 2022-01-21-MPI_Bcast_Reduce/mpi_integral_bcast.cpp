#include "mpi.h"
#include <cstdio>

/* Problem parameters */
double f(double x);

int main(int argc, char **argv)
{
  /* MPI Variables */
  int dest, noProcesses, processId, src, tag;
  MPI_Status status;

  /* problem variables */
  int i;
  double area, at, heigth, width, total, range, lower;
  int numberRects;
  double lowerLimit;
  double upperLimit;


  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &noProcesses);
  MPI_Comm_rank(MPI_COMM_WORLD, &processId);

  /* read, send, and receive parameters */
  tag = 0;
  if (0 == processId) {
    fprintf(stderr, "Enter number of steps: \n");
    scanf("%d", &numberRects);
    fprintf(stderr, "Enter lower limit: \n");
    scanf("%lf", &lowerLimit);
    fprintf(stderr, "Enter upper limit: \n");
    scanf("%lf", &upperLimit);
  }

  /* Broadcast the read data parameters*/
  MPI_Bcast(&numberRects, 1, MPI_INT,    0, MPI_COMM_WORLD);
  MPI_Bcast(&lowerLimit,  1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&upperLimit,  1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

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

  /* Collect and reduce data */
  MPI_Reduce(&area, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  /* print results */
  if (0 == processId) { /* Master */
    std::fprintf(stderr, "The area from %g to %g is : %25.16e\n", lowerLimit, upperLimit, total);
  }

  /* finish */
  MPI_Finalize();

  return 0;
}

double f(double x) {
  return x*x;
}
