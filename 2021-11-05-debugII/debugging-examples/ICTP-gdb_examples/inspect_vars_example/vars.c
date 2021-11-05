#include<stdio.h>
#include<string.h>

int main( int argc, char *argv[] )
{
          double mydouble = 3.14 / 3;
          float  myfloat  = 3.3;
          char   mychar   = 'B';
          int    myIntArray[10];
          int    MyNegativeInt = -1;
          char   myString[20];

          struct foo {
             char *name;
             int  EyeColour;
           } myStruct; 

          strncpy(myString, "hello", 19);
          int i;
          for (  i = 0; i < 10; i++ )
              myIntArray[i] = i;
   
          return 0;
}

