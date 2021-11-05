#include <stdio.h>
 
void first_function(void);
void second_function(int);
   
int main(void)
{
     printf("hello world\n");
     first_function();
     printf("goodbye goodbye\n");
  
     return 0;
}
 
void first_function(void)
{
     int data = 8;
     char t = 'c';
     void *point = NULL;
     second_function(data);
     data = 10;
}
  
void second_function(int a)
{
     int b = a;   
     int i;
     for ( i=0; i<b; ++i ) 
          printf("i is %d\n", i);                                    
}
 
