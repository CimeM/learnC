#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include <unistd.h>
#include <getopt.h>
#include <sys/param.h>


#define PI 3.14159265

int main() {
	
	int i;
	int N = 10;

	float fr_1000 = 1000;

	//Frequencies vector there is no sweep function so this vector has a value 10000 on all places
	float **f_out;
	f_out = (float **)malloc(N * sizeof(float *));
	for (i=0; i < N; i++) {
	    f_out[i] = &fr_1000;
	}
 
	for(i = 0; i < N; i++) {
                    printf("%7d %7d\n", (int)*f_out[i], (int)*f_out[i]);
                }

	for (i=0; i < N; i++) {
	printf("vrednost f_out[%d] je %d\n",i, (int)*f_out[i]);
	
	}


return 1;
}