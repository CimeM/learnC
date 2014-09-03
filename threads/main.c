#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[1];
int fd1[2];
int fd2[2];
double lcrpPrams[6];

void* lcr(void *conversation_pipes)
{
    int     writing_result, reading_result;
    char    ch='A';
    char    ch1;
    //double read_buff;
     while(1){


        // reading from pipe no#2
        reading_result = read (fd2[0],&ch1,1);
        if (reading_result != 1) {
          perror("read error");
          exit(3);
        }

        printf("read_buff = %c\n", ch1 );

        //random delay simulating lcr working delays

        // calculating data for amking some computational output


        // writing to pipe no#1
        writing_result = write (fd1[1], &ch,1);

        if (writing_result != 1){
            perror ("write to pipe 1 error");
            exit (2);
        }

        printf ("Writer: %c\n", ch);
        if(ch == 'Z')
            ch = 'A'-1;
        ch++;
   }

    return NULL;
}



int main(void)
{
    int err, pipecreation_result, result1;
    int sending_to_lcr;


    /* creating pipes 0-reading, 1-writig */
    pipecreation_result = pipe(fd1);
    if (pipecreation_result < 0){
       perror("error pipe 1 creation ");
       exit(1);
    }

    pipecreation_result = pipe(fd2);
    if (pipecreation_result < 0){
       perror("error pipe 2 creation ");
       exit(1);
    }

    
    /* creating thread 
     * new thread will share file descriptors to the parent (main())
    */
    err = pthread_create(tid, NULL, &lcr, (void *) NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n Thread created successfully\n");

    while(1){

        char ch = 'D';

        /*  */
        lcrpPrams[0] = 1;
        lcrpPrams[1] = 2;
        lcrpPrams[2] = 3;
        lcrpPrams[3] = 4;
        lcrpPrams[4] = 5;

        
        

        /* wrinting to a pipe to send arguments to lcr thread */
        sending_to_lcr = write (fd2[1], &ch ,1 );
        if (sending_to_lcr != 1){
            perror ("error at to pipe 2 (sendong data to lcr)");
        }


        /* reading from a pipe */
        //close (fd1[1]);


        result1 = read (fd1[0],&ch,1);
        if (result1 != 1) {
          perror("read error");
          exit(3);
        }

        printf ("Reader: %c\n", ch);  
    }




    sleep(1);
    return 0;
}