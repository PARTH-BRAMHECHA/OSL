#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Global variables
pthread_mutex_t count_mutex, resource_mutex;
int readers = 0;
int data = 0;

// Writer thread function
void *writer(void *id) {
    while (1) {
        pthread_mutex_lock(&resource_mutex);
        printf("Writer is writing the resource\n");
        data = 1 + data;
        pthread_mutex_unlock(&resource_mutex);
        sleep(5);
    }
}

// Reader thread function
void *reader(void *id) {
    while (1) {
        pthread_mutex_lock(&count_mutex);
        readers++;
        if (readers == 1) {
            pthread_mutex_lock(&resource_mutex);
        }
        pthread_mutex_unlock(&count_mutex);

        // Reading data
        printf("Reader is reading the resource\t");
        printf("data = %d\n", data);

        pthread_mutex_lock(&count_mutex);
        readers--;
        if (readers == 0) {
            pthread_mutex_unlock(&resource_mutex);
        }
        pthread_mutex_unlock(&count_mutex);

        sleep(5);
    }
}

int main() {
    int r, w;
    printf("Enter Number of readers: ");
    scanf("%d", &r);
    printf("Enter Number of writers: ");
    scanf("%d", &w);

    pthread_t reader_threads[r];
    pthread_t writer_threads[w];

    // Initialize mutexes
    pthread_mutex_init(&count_mutex, NULL);
    pthread_mutex_init(&resource_mutex, NULL);

    // Create reader and writer threads
    for (int i = 0; i < r; i++) {
        pthread_create(&reader_threads[i], NULL, reader, NULL);
    }
    for (int i = 0; i < w; i++) {
        pthread_create(&writer_threads[i], NULL, writer, NULL);
    }

    // Join threads
    for (int i = 0; i < r; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for (int i = 0; i < w; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    // Destroy mutexes
    pthread_mutex_destroy(&resource_mutex);
    pthread_mutex_destroy(&count_mutex);

    return 0;
}
