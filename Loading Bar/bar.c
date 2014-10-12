#include <stdio.h>

#define DOTS_10 ".........."
#define SPAC_10 "          "
int main(void)
{
	int i;
    for ( i=1; i <= 100; i++) {
        usleep(10000);
        loadBar( i , 100, 100, 70); 
    }
    printf("\nDone!\n");
    return 1;
}

// Process has done i out of n rounds,
// and we want a bar of width w and resolution r.
int loadBar(int x, int n, int r, int w)
{
    // Only update r times.
    if ( x % (n/r +1) != 0 ) return;
 
    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;
 
    // Show the percentage complete.
    printf("%3d%% [", (int)(ratio*100) );
 
    // Show the load bar.
    for (x = 0; x < c; x++){
    	printf("=");}

    for (x=c; x<w; x++)
    {printf(" ");}
 
    // ANSI Control codes to go back to the
    // previous line and clear it.
	// at 100% print out the full progress bar
	if (ratio != 1 ){
    printf("]\n\033[F\033[J");
	}
	else{
		printf("]\n");
	}
}