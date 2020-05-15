#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void main(int argc, char* argv[])
{
    double n;
    printf(" Enter value for n : ");
    scanf("%lf", &n);
    double x,y;
    int i, count=0;
    double z,pi;
    clock_t starttime, endtime, totaltime;
    srand(time(NULL));
    starttime = clock();
    for (i=0; i<n; ++i)
    {
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        z = sqrt((x*x)+(y*y));

        if (z<=1)
        {
            ++count;
        }
    }
    pi = ((double)count/(double)n)*4.0;
    printf("Pi value : %f\n", pi);
    endtime = clock();
    float diff = ((float)endtime - (float)starttime)/CLOCKS_PER_SEC;
    printf("Calculating time is: %f second",diff );
}
