#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include<time.h>

int main(int argc, char* argv[])
{
    int n= 100000000;// n value
    double x,y;
    int i, count=0;
    double z, pi;
    int numofthreads = atoi(argv[1]);// number of threads
    int nit = ceil(n/numofthreads);
    double starttime,stoptime;
    start = omp_get_wtime();

    #pragma omp parallel firstprivate(x, y, z, i) reduction(+:count) num_threads(numofthreads)
    {
        srandom((int)time(NULL) ^ omp_get_thread_num());
        for (i=0; i<nit; ++i)
        {
            x = (double)random()/RAND_MAX;
            y = (double)random()/RAND_MAX;
            z = sqrt((x*x)+(y*y));
        if (z<=1)
        {
                ++count;
        }
    }

    }
        pi = ((double)count/(double)(n))*4.0;
        printf("Pi value: %f\n", pi);
    stoptime = omp_get_wtime();
    printf("Time Taken: %f\n",stoptime-starttime);
    return 0;
}
