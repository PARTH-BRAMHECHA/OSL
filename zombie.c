#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sort_ascending(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] > arr[j]) {
                // Swap elements
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sort_descending(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] < arr[j]) {
                // Swap elements
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    pid_t p;
    int arr[] = {5, 2, 9, 1, 5, 6};  // Example array
    int n = sizeof(arr)/sizeof(arr[0]);

    p = fork();

    if (p < 0) {
        printf("Error in making child\n");
        return 1;
    }

    // Child process
    if (p == 0) {
        printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Child: Sorting in ascending order\n");
        sort_ascending(arr, n);
        printf("Child: Sorted array (ascending): ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Child exits without being cleaned up immediately
        exit(0);  // Child exits but the parent won't call wait yet, creating a zombie
    }

    // Parent process
    else {
        printf("Parent: PID = %d, Child PID = %d\n", getpid(), p);
        printf("Parent: Sorting in descending order\n");
        sort_descending(arr, n);
        printf("Parent: Sorted array (descending): ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Parent delays calling wait, creating a zombie
        printf("Parent: Delaying the cleanup of child process...\n");
        sleep(5);  // Sleep to allow the child to remain a zombie for a while
        
        // Clean up the child process
        wait(NULL);  // Parent now collects the exit status of the child, cleaning up the zombie
        printf("Parent: Child process cleaned up.\n");
    }

    return 0;
}
