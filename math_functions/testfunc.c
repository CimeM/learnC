/*
*functions are initialized here. they are goig to be used in file tes.c
*this file ism met for making the file test.c clean and eay to read
*functions for testing purposes will be delcalred here
*credated by: Martin Cimerman
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float max_array(float *arrayptr, int numofelements) {
  int i = 1;
  float max = -100000;

  for(i; i < numofelements; i++)
  {
    if(max < arrayptr[i])
    {
      max = arrayptr[i];
    }
  }
  return max;
}

float mean_array(float *arrayptr, int numofelements) {
  int i = 1;
  float mean = 0;

  for(i; i < numofelements; i++)
  {
  	mean += arrayptr[i];
  }

  mean = mean / (float)numofelements;
  return mean;
}

float *trapz(float *arrayptr, float *dT, int size) {
  float *result = (float *)malloc(sizeof(float));
  int i;
  //printf("size = %d\n", size);
  for (i =0; i < size ; i++) {
    result[0] += fabsf((dT[ i+1 ] - dT[ i ]) * ( arrayptr[i] - arrayptr[ i+1 ] )/(float)2);
  }
    return result;
}