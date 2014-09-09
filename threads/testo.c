#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define data_values 3
#define num_steps 13


int main ()
{

   char buffer[90*sizeof(char)];
   char data[90*sizeof(char)];
   int step;
   int i;

   int s;
   float **recived_data;
   recived_data = (float **)malloc((data_values-1) * sizeof(float *));
      for(s = 0; s < (data_values+1); s++) {
         recived_data[s] = (float *)malloc(num_steps * sizeof(float));
      }
   

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
   int t, u;
   for(u = 0; u  <= num_steps-1; u++) 
   {
      //printf("step = %d\n",u+1);
      for (t = 0; t <= (data_values-1); t++)
      {
         printf("%f\n", recived_data[t][u]);
      }
   }

   if (pclose(f) < 0)
   {
       printf("ERROR pclose;");
   }

   return 0;
}

