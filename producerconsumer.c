#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BufferSize 5

sem_t empty;
sem_t full;
int buffer[BufferSize];
pthread_mutex_t mutex;
int in = 0, out = 0;

// Display function used for producer
void display_pro() {
    int i;
    
    if (out == -1)
        return;
    
    if ((out == in + 1) || (out == in)) {
        printf("Queue: ");
        int i = out;
        int counter = 1;
        while (counter <= BufferSize) {
            printf("%d ", buffer[i]);
            i = (i + 1) % BufferSize;
            counter++;
        }
    } else {
        printf("Queue: ");
        for (i = out; i != in; i = (i + 1) % BufferSize) {
            printf("%d ", buffer[i]);
        }
    }
    printf("\n");
}

// Display function for consumer
void display() {
    int i;
    if (out == -1)
        return;
    
    printf("Queue: ");
    for (i = out; i != in; i = (i + 1) % BufferSize) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void *producer(void *pno) {
    while (1) {
        int item;
        for (int i = 0; i < BufferSize; i++) {
            item = rand() % 10; // Produce a random item between 0 and 9
            sem_wait(&empty);
            pthread_mutex_lock(&mutex);
            
            printf("\nProducer P[%d]: has produced item %d at position %d.\n", *((int *)pno), item, in);
            buffer[in] = item; // Inserting item at the end of the queue
            in = (in + 1) % BufferSize; // Updating end point of the queue
            
            display_pro(); // Display queue
            
            sleep(2);
            pthread_mutex_unlock(&mutex); // Unlocking the mutex
            sem_post(&full);
        }
    }
}

void *consumer(void *cno) {
    while (1) {
        for (int i = 0; i < BufferSize; i++) {
            sem_wait(&full);
            pthread_mutex_lock(&mutex);
            int item = buffer[out];
            printf("\nConsumer C[%d]: has consumed item %d from position %d.\n", *((int *)cno), item, out);
            out = (out + 1) % BufferSize;
            
            display();
            sleep(3);
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
        }
    }
}

int main() {
    pthread_mutex_init(&mutex, NULL); // Initialize mutex
    sem_init(&empty, 0, BufferSize); // Initialize semaphore empty
    sem_init(&full, 0, 0); // Initialize semaphore full

    int producers, consumers;
    
    // Taking input from user about number of producers and consumers
    printf("---Producer Consumer Problem---\n");
    printf("Enter number of producers: ");
    scanf("%d", &producers);
    printf("Enter number of consumers: ");
    scanf("%d", &consumers);
    
    pthread_t pro[producers], con[consumers];
    int p[producers], c[consumers];
    
    printf("\nEnter ID of Producers:\n");
    for (int i = 0; i < producers; i++) {
        printf("ID of Producer[%d]: ", i + 1);
        scanf("%d", &p[i]);
    }
    
    printf("\nEnter ID of Consumers:\n");
    for (int i = 0; i < consumers; i++) {
        printf("ID of Consumer[%d]: ", i + 1);
        scanf("%d", &c[i]);
    }
    
    printf("\n\n----------------------\n");
    printf("Press ctrl+c to stop execution\n");
    printf("----------------------\n");
    
    // Creating producers
    for (int i = 0; i < producers; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&p[i]);
    }
    
    // Creating consumers
    for (int i = 0; i < consumers; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&c[i]);
    }
    
    // Joining producers
    for (int i = 0; i < producers; i++) {
        pthread_join(pro[i], NULL);
    }
    
    // Joining consumers
    for (int i = 0; i < consumers; i++) {
        pthread_join(con[i], NULL);
    }
    
    // Destroying mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
