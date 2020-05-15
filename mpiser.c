
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float randNumGen(){

   int random_value = rand();
   float unit_random = random_value / (float) RAND_MAX;
   return unit_random;
}

int main(int argc, char *argv[])
{

   srand ( time(NULL) );
   float in_count=0;
   float tot_count=0;
   int tot_iterations=10000000;
   int counter=0;

   for(counter=0;counter<tot_iterations;counter++){
      float x = randNumGen();
      float y = randNumGen();

      float result = sqrt((x*x) + (y*y));

      if(result<1){
         in_count+=1;         
      }
      tot_count+=1;

   }

   float pi=4*in_count/tot_count;
   printf("The value of Pi is : %f\n",pi);



}
