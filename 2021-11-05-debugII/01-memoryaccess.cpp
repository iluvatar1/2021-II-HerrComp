#include <iostream>

int main(void)
{
  //double x[10], y[5]; // imprime raro
  double y[5], x[10]; // imprime 1
for(int ii = 0; ii < 5; ++ii) {
    y[ii] = ii +1;
}
for(int ii = 0; ii < 10; ++ii) {
    x[ii] = -(ii +1);
}

double z = x[10];
  std::cout << z << std::endl;

  return 0;
}
