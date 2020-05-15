#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[])
{
    double x,y;
    long long int i;
    long int count=0;
    double z, pi;
    int numthreads = atoi(argv[1]);// number of threads
    long long int total = 1000000; // n value
    double starttime,stoptime;
        srandom((int)time(NULL) ^ omp_get_thread_num());
        starttime = omp_get_wtime();
        #pragma omp parallel for  firstprivate(x, y, z, total) reduction(+:count) num_threads(numthreads)
        for (i=0; i<total; ++i)
        {
            x = (double)random()/RAND_MAX;
            y = (double)random()/RAND_MAX;
            z = sqrt((x*x)+(y*y));
        if (z<=1)
        {
                ++count;
        }

    }
stoptime = omp_get_wtime();
        pi = ((double)count/(double)(total))*4.0;
        printf("Pi value : %f\n", pi);

        printf("time Taken: %f\n",stoptime-starttime);

    return 0;
}
