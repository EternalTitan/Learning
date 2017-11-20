//File name: a.c
#include <stdio.h>
#include <string.h>
#include <mpi.h> 
#include <time.h>
#include <stdlib.h>

void merege(int c[], int nc, int a[], int na, int b[], int nb);
void print(int x[], int nx);
void sort(int x[], int nx);

int main(void) 
{
  int *a = NULL, *b = NULL, *c = NULL;
  int        comm_sz;
  int        my_rank;
  time_t t;
  int i, na, nb, nc;

  MPI_Init(NULL, NULL); 
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

  srand((unsigned) time(&t));
//   na = rand()%50+51;
//   nb = rand()%50+51;
  na=70;
  nb=80;
  nc= na+nb;

  if(my_rank == 1){
    a = (int *) malloc(na * sizeof(int));
    for (i=0;i<na;i++)
    {
        a[i]=rand()%100;
    }
    sort(a,na);
    print(a,na);
    MPI_Send(a, na, MPI_INT, 0, 0, MPI_COMM_WORLD);
  //Complete the rest of the block.
  
  }

  if(my_rank == 2){
    b = (int *) malloc(nb * sizeof(int));
    for (i=0;i<nb;i++)
    {
        b[i]=rand()%100;
    }
    sort(b,nb);
    print(b,nb);
    MPI_Send(b, nb, MPI_INT, 0, 0, MPI_COMM_WORLD);
  //Complete the rest of the block.
  }

  if(my_rank == 0){
    a = (int *) malloc(na * sizeof(int));
    b = (int *) malloc(nb * sizeof(int));
    c = (int *) malloc((na+nb) * sizeof(int));
    MPI_Recv(a,na,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    MPI_Recv(b,nb,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    
    merege(c,nc,a,na,b,nb);
    print(c,nc);

  //Complete the rest of the block.
  } 
  MPI_Finalize(); 
   return 0;
};

int findIndexOfSmallest(int a[], int from, int to){
  //Look at your project 1 to complete this function
    int mi,i;
    mi=from;
    for (i=from;i<to;i++)
    {
        if (a[i]<a[mi])
        {
            mi=i;
        }
    }
    return mi;
};

void sort(int x[], int nx){
  //Look at your project 1 to complete this function
  int temp,i,mi;
  for (i=0;i<nx;i++)
  {
    mi=findIndexOfSmallest(x,i,nx);
    temp=x[i];
    x[i]=x[mi];
    x[mi]=temp;
  }
}

void merege(int c[], int nc, int a[], int na, int b[], int nb){
  //Look at your project 1 to complete this function
  int i,j;
  i=0;
  j=0;
  nc=na+nb;
    while (i+j<nc)
    {
        if (i==na)
        {
            c[i+j]=b[j++];
        }
        else if (j==nb)
        {
            c[i+j]=a[i++];
        }
        else
        {
            if (a[i]<b[j])
            {
                c[i+j]=a[i++];
            }
            else
            {
                c[i+j]=b[j++];
            }
        }
    }
}

void print(int x[], int nx){
  //This function is complete. Do not change it.
  int i;
  for(i = 0; i < nx; i++)
    printf("%d, ", x[i]);
  printf("\n************************\n");
}
