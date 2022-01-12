#include "mpi.h"
#include <stdio.h>

/* Problem parameters */
double f(double x) {
  return x*x;
}
const int numberRects = 600000000;
const double lowerLimit = 2.0;
const double upperLimit = 5.0;


int main(int argc, char **argv)
{
  int pid = 0, np = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  
  int i;
  double area, at, heigth, width;

  area = 0.0;
  width = (upperLimit - lowerLimit) / numberRects;

  int Nlocal = numberRects/np;
 
  for (i = pid*Nlocal; i < (pid+1)*Nlocal; ++i) {
    at = lowerLimit + i*width + width/2.0;
    heigth = f(at);
    area = area + width*heigth;
  }

  //printf("The area from %lf to %lf is : %lf\n", pid*Nlocal*width, (pid+1)*Nlocal*width, area);
  int tag = 0;
  double totalArea = 0.0;
  if (0 == pid) {
    double buffer = 0;
    totalArea = area;
    for (int src = 1; src < np; ++src) {
      MPI_Recv(&buffer, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      totalArea += buffer;
    }
    printf("The area from %lf to %lf is : %lf\n", lowerLimit, upperLimit, totalArea);
  } else {
    //send area to pid 0;
    int dest = 0;
    MPI_Send(&area, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
  return 0;
}
