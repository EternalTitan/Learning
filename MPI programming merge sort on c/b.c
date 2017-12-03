#include <stdio.h>
//#include <string.h>
#include <mpi.h>
#include <stdlib.h>

int main(void) {
    int i, my_rank, comm_sz, sum = 0, n = -1;
    int *receive_vector;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    srand((unsigned) time(&t));
    n = rand() % 90 + 10;
    MPI_Bcast(&n, 1, MPT_INT, 0, MPI_COMM_WORLD);
    receive_vector = (int *) malloc(n * sizeof(int));
    if (my_rank == 0)
        for (i = 0; i < n; i++)
            receive_vector[i] = rand() % 100;
    MPI_Bcast(&receive_vector, n, MPT_INT, 0, MPI_COMM_WORLD);
    int tot = 0;
    for (i = 0; i < n; i++)
        tot += receive_vector[i];
    printf("In process %d the sum is: %d\n", my_rank, tot);

    return 0;
}
