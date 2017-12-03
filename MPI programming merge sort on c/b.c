#include <stdio.h>
//#include <string.h>
#include <time.h>
#include <mpi.h>
#include <stdlib.h>

int main(void) {

    int i, my_rank, comm_sz, sum, n = -1;
    int *receive_vector;
    time_t t;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    srand((unsigned) time(&t));
    if (my_rank == 0)
    {
        n = rand() % 90 + 10;
    }
//    n=10;
//    printf("my_rank is %d  n is %d\n",my_rank,n);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    receive_vector = (int *) malloc(n * sizeof(int));
    if (my_rank == 0)
        for (i = 0; i < n; i++)
        {
            receive_vector[i] = rand() % 100;
//            printf("receive_vector[%d]=   %d\n",i,receive_vector[i]);
        }
    MPI_Bcast(receive_vector, n, MPI_INT, 0, MPI_COMM_WORLD);
//    printf("In process %d hit the barrier\n", my_rank);
//    MPI_Barrier(MPI_COMM_WORLD);


//    for (i = 0; i < n; i++)
//    {
//        printf("In process %d receive_vector[%d] is %d\n", my_rank,i,receive_vector[i]);
//    }


//    sum = (int *) malloc(2*sizeof(int));
    sum = 0;
//    MPI_Barrier(MPI_COMM_WORLD);

//    printf("In process %d hit the barrier 222\n", my_rank);
//    printf("In process %d the sum is: %d\n", my_rank, sum);
    for (i = 0; i < n; i++)
    {
//        printf("In process %d receive_vector[%d] is %d\n", my_rank,i,receive_vector[i]);
        sum += receive_vector[i];
//        printf("In process %d sum is %d\n", my_rank,sum);
    }
    printf("In process %d the sum is: %d\n", my_rank, sum);

    MPI_Finalize();

    return 0;
}
