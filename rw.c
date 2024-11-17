#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READS 5
#define NUM_WRITES 5

sem_t write_lock, read_lock, read_count_lock; // Renamed semaphores for clarity
int read_count = 0;        // Number of readers currently reading
int shared_data = 0;       // The shared data

void *reader(void *arg) {
    for (int i = 0; i < NUM_READS; i++) {
        sem_wait(&read_count_lock); // Protect access to read_count

        read_count++;
        if (read_count == 1) {
            sem_wait(&write_lock); // First reader locks write access
        }
        sem_post(&read_count_lock);

        // Reading the shared data
        printf("Reader reads: %d\n", shared_data);
        sleep(1); // Simulate reading time

        sem_wait(&read_count_lock);
        read_count--;
        if (read_count == 0) {
            sem_post(&write_lock); // Last reader unlocks write access
        }
        sem_post(&read_count_lock);
        sleep(1); // Simulate time between reads
    }
    return NULL;
}

void *writer(void *arg) {
    for (int i = 0; i < NUM_WRITES; i++) {
        sem_wait(&read_lock); // Ensure only one writer accesses shared_data
        sem_wait(&write_lock); // Only one writer allowed at a time

        shared_data = rand() % 100; // Writing new data
        printf("Writer writes: %d\n", shared_data);
        sleep(1); // Simulate writing time

        sem_post(&write_lock);
        sem_post(&read_lock); // Release for other writers or readers
        sleep(2); // Simulate time between writes
    }
    return NULL;
}

int main() {
    pthread_t readers[3], writer_thread;

    sem_init(&write_lock, 0, 1);      // Semaphore for writer access
    sem_init(&read_lock, 0, 1);       // Semaphore for reader/writer coordination
    sem_init(&read_count_lock, 0, 1); // Protects access to read_count

    // Create reader and writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }
    pthread_create(&writer_thread, NULL, writer, NULL);

    // Join reader and writer threads
    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    pthread_join(writer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&write_lock);
    sem_destroy(&read_lock);
    sem_destroy(&read_count_lock);

    return 0;
}
