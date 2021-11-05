/* Program: debugme.c
 * Purpose: To provide experience with the DDD debugger.
 * Author:  Marge Coahran
 * CSC201, Spring 2007
 */

#include <stdio.h>


/* MAIN PROGRAM */
int main() {
  int size = 15;
  int myArray[15];
  /* NOTE: for ddd to display myArray, it must be allocated with a constant
   * number of elements (as opposed to "int myArray[size]" */

  /* load array with even integers */
  int i = 0;
  while (i < size) {
    myArray[i] = 2*i;
  }
  
  /* print the values in reverse order */
  int j;
  for (j = size-1; j>=0; j++) {
    printf("%d\n", myArray[j]);
  }
  
  /* print values in original order */
  int k;
  for (k = 0; k < size; j++) {
    printf("%d\n", myArray[k]);
  }

  /* print values in original order */
  for (k = 0; k < size; k++); {
    printf("%d\n", myArray[k]);
  }

  return 0;
}
