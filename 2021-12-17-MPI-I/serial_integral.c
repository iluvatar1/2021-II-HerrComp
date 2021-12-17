  /*mpi-V2.c */
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
    int i;
    double area, at, heigth, width;

    area = 0.0;
    width = (upperLimit - lowerLimit) / numberRects;

    for (i = 0; i < numberRects; ++i) {
      at = lowerLimit + i*width + width/2.0;
      heigth = f(at);
      area = area + width*heigth;
    }

    printf("The area from %lf to %lf is : %lf\n", lowerLimit, upperLimit, area);

    return 0;
  }
