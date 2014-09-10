#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define data_values 3
#define num_steps 1  // one size smaller than steps number

/* thread ID */
pthread_t tid[2];
/* arguments for lcr  */
int lcr_params[15];

/* lcr thread output data */
float **recived_data;

/* thread termination flag */
int lcr_thread_end = 0;

float **recived_data;

/* concatenates string to create a comand to be called in lcr thread */
char* concat(char *program,
                char *chanel, 
                char *amplitude,
                char *DC_bias,
                char *shunt, 
                char *averaging, 
                char *calib_fnc, 
                char *ref_imp_real, 
                char *ref_imp_imag,
                char *steps,
                char *sweep_fnc,
                char *start_fr,
                char *stop_fr,
                char *scale,
                char *wait)
{
    char *result = malloc(strlen(program) + strlen(chanel)+strlen(DC_bias)+strlen(shunt)+strlen(averaging)+strlen(calib_fnc)+strlen(ref_imp_real)+strlen(ref_imp_imag)+strlen(steps)+strlen(sweep_fnc)+strlen(start_fr)+strlen(stop_fr)+strlen(scale)+strlen(wait)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, program);
    strcat(result, " ");
    strcat(result, chanel);
    strcat(result, " ");
    strcat(result, amplitude);
    strcat(result, " ");
    strcat(result, DC_bias);
    strcat(result, " ");
    strcat(result, shunt);
    strcat(result, " ");
    strcat(result, averaging);
    strcat(result, " ");
    strcat(result, calib_fnc);
    strcat(result, " ");
    strcat(result, ref_imp_real);
    strcat(result, " ");
    strcat(result, ref_imp_imag);
    strcat(result, " ");
    strcat(result, steps);
    strcat(result, " ");
    strcat(result, sweep_fnc);
    strcat(result, " ");
    strcat(result, start_fr);
    strcat(result, " ");
    strcat(result, stop_fr);
    strcat(result, " ");
    strcat(result, scale);
    strcat(result, " ");
    strcat(result, wait);
    return result;
}






void* lcr_call(void *arg)
{
    char buffer[1000*sizeof(char)];
    char data[1000*sizeof(char)];
    /* iterators */
    int step,i;
    

   int s;
   recived_data = (float **)malloc((data_values-1) * sizeof(float *));
      for(s = 0; s < (data_values+1); s++) {
         recived_data[s] = (float *)malloc(num_steps * sizeof(float));
      }



    char program[] = "ssh root@192.168.81.161 ./lcr";
    char chanel[] = "'1";
    char amplitude[] = "1";
    char DC_bias[] = "0";
    char shunt[] = "999";
    char averaging[] = "1";
    char calib_fnc[] = "0";
    char ref_imp_real[] = "0";
    char ref_imp_imag[] = "0";
    char steps[] = "12";
    char sweep_fnc[] = "0";
    char start_fr[] = "4000";
    char stop_fr[] = "10000";
    char scale[] = "1";
    char wait[] = "0'";

    char *command = concat(program,
                chanel, 
                amplitude,
                DC_bias,
                shunt, 
                averaging, 
                calib_fnc, 
                ref_imp_real, 
                ref_imp_imag,
                steps,
                sweep_fnc,
                start_fr,
                stop_fr,
                scale,
                wait);



    printf("%s\n", command);

    //command = "ls";
    FILE *f = popen("ssh root@192.168.81.161 './lcr 1 1 0 999 1 0 0 0 13 1 4000 8000 0 0'", "r");
   if(!f){
         fprintf(stderr, "Could not open pipe for output.\n");
         return 0;
   }
    

   for (step = 0; step <= (num_steps-1); step++)
   {
      fgets(buffer, 90*sizeof(char), f);
      int c =0;
      int d =0;
      /* remove spaces from recived data  */
      while (buffer[c] != '\0')
      {
         if (!(buffer[c] == ' ' && buffer[c+1] == ' ')) {
           data[d] = buffer[c];
           d++;
         }
         c++;
      }

      /* find position of spaces that define data position */
      c=0;
      d=0;
      int spaces[data_values+1];//space on place 0 always present , + 3 data numbers
      while (data[c] != '\0')
      {
         if ((data[c] == ' ')) {
            spaces[d] = c;
            //printf("space = %d\n", c);
           d++;
         }
         c++;
      }

      /* data is extaracted from the string */
      for (i = 0; i <= (data_values -1); i++)
      {  
         //printf("i=%d\n",i );
         //printf("data = %s\n",data);
         sscanf(data, "%f", &recived_data[i][step]);
         //overwrite data that was already read
         c=0;
         while(c < spaces[i+1]){
            data[c] = 32;//ASCII for space
            c++;
         }
      }
   }

   step =0;
   
   

   
    /* flag indicating thread ended its task setting to positive value */
    lcr_thread_end = 1;
    
    /* thread self terminaltion */
    pthread_exit(NULL);
    exit(1);

}

int main(void)
{

    /* TODO older data has to be saved seperatley from workers refresh stream */
    lcr_params[0] = 44;
    
    
    //int s;
    /* data from lcr
     * TODO set right SIZE!!!
     */
    //recived_data = (float **)malloc((data_values-1) * sizeof(float *));
     //   for(s = 0; s < (data_values+1); s++) {
      //      recived_data[s] = (float *)malloc(num_steps * sizeof(float));
       // }

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
        int t, u;
        if (lcr_thread_end == 1 )
        { 
            for(u = 0; u  <= num_steps-1; u++) 
            {
                //printf("step = %d\n",u+1);
                for (t = 0; t <= (data_values-1); t++)
                {
                    printf("%f\n", recived_data[t][u]);
                }
            }
                    lcr_thread_end = 0;
                }

        /* simulation... */
        sleep(1);
    }

    /* never used.. while(1) */
    return 0;
}