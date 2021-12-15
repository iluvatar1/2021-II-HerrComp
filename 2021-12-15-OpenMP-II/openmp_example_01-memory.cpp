#include <omp.h>
#include <iostream>
#include <cstdio>

int main(int argc, char *argv[]) {
  
  int nthreads, tid;
  
  /* Fork a team of threads with each thread having a private tid variable */
#pragma omp parallel private(tid)
  {
    
    /* Obtain and print thread id */
    tid = omp_get_thread_num();
    std::printf("Hello World from thread = %d\n", tid);
    std::cout << "Memory address for tid = " << &tid << std::endl;
    std::cout << "Memory address for nthreads = " << &nthreads << std::endl;
    
    /* Only master thread does this */
    if (tid == 0) 
      {
	nthreads = omp_get_num_threads();
	printf("Number of threads = %d\n", nthreads);
      }
    
  }  /* All threads join master thread and terminate */
  
}
