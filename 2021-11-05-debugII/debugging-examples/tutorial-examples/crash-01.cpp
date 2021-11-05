// from http://www.tutorialspoint.com/gnu_debugger/gdb_debugging_example1.htm

#include <iostream>

using namespace std;

int divint(int, int);

int main() {
  int x = 5, y = 2;
  cout << divint(x, y);
  x =3; y = 0;
  cout << divint(x, y);
  return 0;
}

int divint(int a, int b)
{
  return a / b;
} 
