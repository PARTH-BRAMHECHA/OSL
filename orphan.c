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

        // Sleep to simulate the orphaned state
        sleep(10);  // Child will still be running while the parent exits
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

        // Parent exits before the child, making the child process orphaned
        exit(0);
    }

    return 0;
}
