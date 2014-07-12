/*
*this is the mainn file ment for testing the functionality of functions
*before migrated to lcr meter on red pitaya
*created by Martin Cimerman
*/

#include <stdio.h>
#include <fnc_head_declaration.h>
#include <stdlib.h>



int main()
{
  printf("\n----[START]----\n");
  
  float myArray[]={1,2,3,4,5};
  float *dT;
  float dt[] = {1,2,3,4,5};
  dT=&dt[0];
  int n = sizeof(dt)/sizeof(dt[0]);
  
  float *arrptr = &myArray[0];
  int array_size = sizeof(myArray)/4;

  //testing max_size() function
  float max = max_array(arrptr,array_size);
  printf("max value of an array is :%.3f\n",max);

  //testing mean_array() function
  float mean = mean_array(arrptr,array_size);
  printf("mean value of array is:%f\n",mean );

  float *trapz_result;
  trapz_result = trapz(arrptr, dT, n);
  printf("result from trapezoidal method :%f\n",trapz_result[0]);

  printf("-----[END]-----\n\n");
  return 0;
}