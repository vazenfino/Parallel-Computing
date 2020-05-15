#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#define SEED 35791246

int main(int argc, char* argv[])
{
    long niter = 1000000000;
    int myid, node_num;
    double x,y;
    int i, count=0;
    double z, pi;


    float start,finish;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &node_num);
    int recieved[node_num];
    long recvniter[node_num];
    srand(SEED+myid);

    start = MPI_Wtime();

    if(myid != 0)
    {
        for (i=0; i<niter; ++i)
        {
            x= ((double)rand())/RAND_MAX;
            y =((double)rand())/RAND_MAX;
            z = sqrt(x*x+y*y);
            if (z<=1)
            {
                count++;
            }
        }
        for(i=0; i<node_num; ++i)
        {
            MPI_Send(&count,
                                 1,
                                 MPI_INT,
                                 0,
                                 1,
                                 MPI_COMM_WORLD);
            MPI_Send(&niter,
                                 1,
                                 MPI_LONG,
                                 0,
                                 2,
                                 MPI_COMM_WORLD);
        }
    }
    else if (myid == 0)
    {
        for(i=0; i<node_num; ++i)
        {
            MPI_Recv(&recieved[i],
                                 node_num,
                                 MPI_INT,
                                 MPI_ANY_SOURCE,
                                 1,
                                 MPI_COMM_WORLD,
                                 MPI_STATUS_IGNORE);
            MPI_Recv(&recvniter[i],
                                 node_num,
                                 MPI_LONG,
                                 MPI_ANY_SOURCE,
                                 2,
                                 MPI_COMM_WORLD,
                                 MPI_STATUS_IGNORE);
        }
    }

    if (myid == 0)
    {
        int finalcount = 0;
        long finalniter = 0;
        for(i = 0; i<node_num; ++i)
        {
            finalcount += recieved[i];
            finalniter += recvniter[i];
        }

        pi = ((double)finalcount/(double)finalniter)*4.0;
        printf("Pi: %f\n", pi);


finish = MPI_Wtime();
float diff =finish-start;
		printf("Calculating time is %f millisecond",diff );
    }

    MPI_Finalize();
    return 0;
}
