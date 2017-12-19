//File name: a.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define thread_count 	10
#define ASCIIs		127		//ASCII characters from 0 to 127
#define atmost		1000

char letters[atmost+1]; //extra location for '\0'.
int count[ASCIIs], h;	//h holds the length of the segment
pthread_mutex_t mutex[ASCIIs];

void *task(void* rank);

int main(){
    pthread_t* thread_handles;
    int i, thread;
    for (i=0;i<ASCIIs;i++)
        count[i]=0;
    printf("Please input a line.\n");
    gets(letters);
    h = strlen(letters);
    while (h%thread_count!=0)
    {
        strcat(letters," ");
        h+=1;
    };
    for (i=0;i<ASCIIs;i++)
    {
        pthread_mutex_init(&mutex,NULL);
//        mutex[i]= PTHREAD_MUTEX_INITIALIZER;
    }
    thread_handles = malloc(thread_count* sizeof(pthread_t));
    for (thread=0;thread<thread_count;thread++)
    {
        pthread_create(&thread_handles[thread],NULL,task,(void*) thread);
    }
    for (thread=0;thread<thread_count;thread++)
    {
        pthread_join(thread_handles[thread],NULL);
    }

    /*
      Assign count[i]’s by 0
      prompt the user to enter a line.
      Read the line. The C function gets(letters) reads a line into the array: letters.
      Add spaces to the end of the line to make its length divisible by thread_count.
          The C function: strlen(letters) returns the length of the string.
        The C function: strcat(letters, “ “ adds a single spave to the end of the string.
      initialize mutex[i] for i=0,..., ASCIIs.
  Create thread_count threads. Each of them calls the function: task. Note that change the value to different numbers like 2, 5, 10, 20,..., 50 to test your program.
  Join the threads and destroy all the mutex[i].
  print the array count like I did in the serial program.
    */

    for(i = 33; i < ASCIIs; i++){
        if(count[i] != 0)
            printf("Number of %c is: %d\n", i, count[i]);
    }
    return 0;
}

void *task(void* rank){
    /*
      Each thread executes this function for a segment of the line. It is important no two threads try
  to change the content of count[index] at the same time. Note that it is ok if one thread changes
  count[m] and another thread changes count[n], where the value of m and n are different.
  The last segment may not be the same size of other segments.
    */
    int i,ch,myrank;
    myrank = (int) rank;
    for (i=h/thread_count*myrank;i<h/thread_count*(myrank+1);i++)
    {
        ch =letters[i];
        pthread_mutex_lock( &mutex[ch] );
        count[ch]+=1;
        pthread_mutex_unlock( &mutex[ch] );
    }

    return NULL;
}
