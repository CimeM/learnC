#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[1];
int fd1[2];
int fd2[2];

void* lcr(void *conversation_pipes)
{
    int     result;
    char    ch='A';

     while(1){
        result = write (fd1[1], &ch,1);

        if (result != 1){
            perror ("write to pipe 1 error");
            exit (2);
        }

        printf ("Writer: %c\n", ch);
        sleep(2);
        if(ch == 'Z')
            ch = 'A'-1;
        ch++;
        sleep(1);
   }

    return NULL;
}



int main(void)
{
    int err, result, result1;


    /* creating pipes */
    result = pipe(fd1);
    if (result < 0){
       perror("error pipe 1 ");
       exit(1);
    }

    result = pipe(fd2);
    if (result < 0){
       perror("error pipe 2");
       exit(1);
    }
    printf("\n Pipes created successfully\n");



    
    /* creating thread */
    err = pthread_create(tid, NULL, &lcr, (void *) NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n Thread created successfully\n");



    /* reading from a pipe */
    while(1){
      char    ch;

      result1 = read (fd1[0],&ch,1);
      if (result1 != 1) {
        perror("read error");
        exit(3);
      }

      printf ("Reader: %c\n", ch);   
      sleep(1);
    }




    sleep(1);
    return 0;
}