#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>

int main(int argc, char* argv[])
{
    int niter = 1000000000;
    int myid;
    double x,y;
    int i;
    int count=0;
    double z;
    double pi;
    int reducedcount;
    int reducedniter;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

/* Everyone can do the work */

    for (i=0; i<niter; ++i)
    {
        srand48(time(NULL)+myid);
        x = (double)random()/RAND_MAX;
        y = (double)random()/RAND_MAX;
        z = sqrt((x*x)+(y*y));
        if (z<=1)
        {
            ++count;
        }
    }


    MPI_Reduce(&count,
                   &reducedcount,
                   1,
                   MPI_INT,
                   MPI_SUM,
                   0,
                   MPI_COMM_WORLD);
    MPI_Reduce(&niter,
                   &reducedniter,
                   1,
                   MPI_INT,
                   MPI_SUM,
                   0,
                   MPI_COMM_WORLD);

    if (myid == 0)
    {
        pi = ((double)reducedcount/(double)reducedniter)*4.0;
        printf("Pi: %f\n%i\n%d\n", pi, reducedcount, reducedniter);
        

    }

    MPI_Finalize();
    return 0;
}
