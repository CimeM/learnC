#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* thread ID */
pthread_t tid[2];
/* arguments for lcr  */
int lcr_params[15];

/* thread termination flag */
int lcr_thread_end = 0;

/* lcr output data */
float *PhaseZ;
float *AmplitudeZ;
float *Frequency;

/* lcr function */
void* lcr_call(void *arg)
{

    /* thread termination id */
    //pthread_t id = pthread_self();

    printf("lcr_params = %d\n",*lcr_params);
    
    /*lcr computation simulation
     * lcr will recive data trough globaly created variable
     * calculate the data and write this data to the file
    */

    //system(/bin/lcr + arguments);
    sleep(4);


    /* writing data to allocated memmory */
    PhaseZ[0]      = 1;
    AmplitudeZ[0]  = 1;
    Frequency[0]   = 1;


    /* thread termination */
    //pthread_exit();

    /* flag for tread termination */
    lcr_thread_end = 1;
    /* thread self terminaltion */
    pthread_exit(NULL);

}

int main(void)
{

    /* TODO older data has to be saved seperatley from workers refresh stream */
    lcr_params[0] = 44;
    
    /* data from lcr
     * TODO set SIZE!!!
     */
    PhaseZ      = (float *)malloc((22 + 1) * sizeof(float) );
    if(PhaseZ == NULL){
        printf("\ncan't allocate");
        return -1;
    }
    AmplitudeZ  = (float *)malloc((22 + 1) * sizeof(float) );
    if(AmplitudeZ == NULL){
        printf("\ncan't allocate");
        return -1;
    }
    Frequency   = (float *)malloc((22 + 1) * sizeof(float) );
    if(Frequency == NULL){
        printf("\ncan't allocate");
        return -1;
    }

    /* calling  */
    int err = pthread_create(&(tid[0]), NULL, &lcr_call, NULL);
    if (err != 0)
        printf("\ncan't create thread:[%s]", strerror(err));
        
    /* simulating workers loop */
    while(1)
    {
        printf("worker running...\n");


        /* when thread ends  data becomes avaliable to worker and JSON
         * flag lcr_thread_end reset
        */
        if (lcr_thread_end == 1 )
        {
            printf("%f   %f   %f  \n",PhaseZ[0] ,AmplitudeZ[0],Frequency[0]);
            lcr_thread_end = 0;
        }

        /* simulation... */
        sleep(1);
    }

    /* never used.. while(1) */
    return 0;
}