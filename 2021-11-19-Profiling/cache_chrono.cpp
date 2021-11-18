#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <iostream>

/*
   Tests cache misses.
*/

template <typename T>
void print_elapsed(T & start, T & end );
void option1(long * data, long isize, long jsize);
void option2(long * data, long isize, long jsize);
void option3(long * data, long isize, long jsize);

int main(int argc, char **argv)
{
  if (argc < 3){
    printf("Usage: cacheTest sizeI sizeJ\nIn first input.\n");
    return 1;
  }
  long sI = atoi(argv[1]);
  long sJ = atoi(argv[2]);

  printf("Operating on matrix of size %ld by %ld\n", sI, sJ);
  auto start = std::chrono::steady_clock::now();
  long *arr = new long[sI*sJ]; // double array.
  auto end = std::chrono::steady_clock::now();
  print_elapsed(start, end);
  
  // option 1
  start = std::chrono::steady_clock::now();
  option1(arr, sI, sJ);
  end = std::chrono::steady_clock::now();
  print_elapsed(start, end);
  
  // option 2
  start = std::chrono::steady_clock::now();
  option2(arr, sI, sJ);
  end = std::chrono::steady_clock::now();
  print_elapsed(start, end);

  // option 3
  start = std::chrono::steady_clock::now();
  option3(arr, sI, sJ);
  end = std::chrono::steady_clock::now();
  print_elapsed(start, end);

  printf("%ld\n", arr[0]);
  
  return 0;
}
  

template <typename T>
void print_elapsed(T & start, T & end )
{
  std::cout << "Elapsed time in ms: "
	    << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
	    << "\n";
}

void option1(long * data, long isize, long jsize)
{
    for (long i=0; i < isize; ++i)
        for (long j=0; j < jsize; ++j)
            data[(i * (jsize)) + j ] = i;
}

void option2(long * data, long isize, long jsize)
{
    for (long i=0; i < isize; ++i)
        for (long j=0; j < jsize; ++j)
            data[(j * (isize)) + i ] = i;
}

void option3(long * data, long isize, long jsize)
{
    for (long i=0; i < isize*jsize; ++i)
            data[i] = i;
}
