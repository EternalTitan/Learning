#include <stdlib.h>
#include <pthread.h>

long long int total_number_of_tosses;	//Total number of tosses
long long int number_in_circle = 0; //Each thread is adding its result to this variable.
int thread_count; //Number of threads.
pthread_mutex_t hitNum_mutex; //To guard the share variable.

void *thread_toss(void* rank); //Each thread calls this function.

int main()
{
    double pi_estimate;//At the end the function main stores the output into this variable and print it.
    long thread; //Use as a control variable in a for-loop.
    pthread_t* thread_handles;

    printf("Enter number of threads and the total number of tosses: ");
    scanf("%d%lld", &thread_count, &total_number_of_tosses);
    //Using the following loop to make it divisible by thread_count.
    while (total_number_of_tosses % thread_count != 0) total_number_of_tosses++;
    //Complete the rest of this function.
    thread_handles = malloc(thread_count* sizeof(pthread_t));
    long long int average_number_of_tosses = total_number_of_tosses / thread_count;
    hitNum_mutex = PTHREAD_MUTEX_INITIALIZER;
    for (thread=0;thread<thread_count;thread++)
    {
        pthread_create(&thread_handles[thread],NULL,thread_toss(),(void*) average_number_of_tosses);
    }
    for (thread=0;thread<thread_count;thread++)
    {
        pthread_join(thread_handles[thread],NULL);
    }
    pi_estimate = 4 * number_in_circle / ((double)number_of_tosses);
    printf("Estimated pi = %f\n", pi_estimate);
    return 0;
}

//returns a random number in the range -1 to 1.
double rand_double() {
    return 2 * (rand() / (double)RAND_MAX) - 1;
}

void *thread_toss(void* rank) {
    //Complete this function
    long long int *data;
    long long int i,tot=0;
    double x,y,distance_squared;
    data = (long long int*) rank;
    for (i = 0; i < data; ++i) {
        x = rand_double();
        y = rand_double();
        distance_squared = x*x + y*y;
        if (distance_squared <= 1)
            tot++;
    }
    pthread_mutex_lock( &hitNum_mutex );
    number_in_circle=number_in_circle+tot;
    pthread_mutex_unlock( &hitNum_mutex );

    return NULL;
}
