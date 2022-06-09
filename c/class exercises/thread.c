#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_OF_THREAD 20
#define NUM_OF_LOOPS 10000

int globalIndx = 0;
void* printFunc(void* tid)
{
        int index;
        static int localIndx = 0;
        int* myid = (int*)tid;
        for(index = 0; index < NUM_OF_LOOPS; index++)
        {
            ++globalIndx;
            ++localIndx;
            printf("Thread ID: %d, Static: %d, Global: %d\n", *(int*)tid, localIndx, globalIndx);

        }
        pthread_exit(NULL);
}

int main(void)
{   
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    int index = 0 , status;
    pthread_t threads[NUM_OF_THREAD];
    for(;index < NUM_OF_THREAD; index++)
    {
        status = pthread_create(&threads[index],NULL ,printFunc, &arr[index]);
        if (status < 0)
        {
            return 1;
        }
    }
    for(index = 0;index < NUM_OF_THREAD; index++)
    {
        pthread_join(threads[index], NULL);
    }
}
