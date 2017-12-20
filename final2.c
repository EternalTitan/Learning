#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

long long int total_number_of_tosses;	//Total number of tosses
long long int number_in_circle = 0; //Each thread is adding its result to this variable.

int main()
{
    double pi_estimate;//At the end the function main stores the output into this variable and print it.

    printf("Enter number of the total number of tosses: ");
    scanf("%lld",  &total_number_of_tosses);

    #pragma omp parallel
    {
        long long int i,tot=0;
        #pragma omp for
        for (i=0;i<total_number_of_tosses;i++)
        {
            double x,y,distance_squared;
            x = rand_double();
            y = rand_double();
            distance_squared = x*x + y*y;
            if (distance_squared <= 1)
                tot++;
        }
        #pragma omp atomic
        number_in_circle += tot;
    };

    pi_estimate = 4 * number_in_circle / ((double)total_number_of_tosses);
    printf("Estimated pi = %f\n", pi_estimate);
    return 0;
}

//returns a random number in the range -1 to 1.
double rand_double() {
    return 2 * (rand() / (double)RAND_MAX) - 1;
}