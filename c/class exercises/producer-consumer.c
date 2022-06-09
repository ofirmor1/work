#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_CP_ITEMS 200
#define BUFFER_SIZE 5
#define NUM_OF_PRODUCERS 3
#define NUM_OF_CONSUMERS 3

sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int index;
int produce = 0;
int consume = 0;
int buffer[BUFFER_SIZE];

void* producer(void* _pruducer)
{   
    int item = 0;
    for (index = 0; index < MAX_CP_ITEMS; index++)
    {
        item++;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[produce] = item;
        printf("producer: %d insert item : %d \n" , *(int*)_pruducer,buffer[produce]);
        produce = (produce + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void* consumer(void* _consumer)
{
    int item;
    for (index = 0; index < MAX_CP_ITEMS; index++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[consume];
        printf("consumer: %d remove item : %d \n", *(int*)_consumer, buffer[consume]);
        consume = (consume + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);  
    }
}

int main()
{
    int index;
    pthread_t prod[NUM_OF_PRODUCERS], cons[NUM_OF_CONSUMERS];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0, BUFFER_SIZE);
    sem_init(&full,0, 0);
    for(index = 0; index < NUM_OF_PRODUCERS; index++)
    {
        pthread_create(&prod[index], NULL, producer, (void*)&index);

    }
    for(index = 0; index < NUM_OF_CONSUMERS; index++)
    {
        pthread_create(&cons[index], NULL, consumer, (void*)&index);
    }
    for(index = 0; index < NUM_OF_PRODUCERS; index++)
    {
        pthread_join(prod[index], NULL);
    }
    for(index = 0; index < NUM_OF_CONSUMERS; index++)
    {
        pthread_join(cons[index], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}

