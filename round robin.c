#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completion; // Completion time
    int remaining_burst; // Remaining burst time for Round Robin
};

// Function to perform Round Robin scheduling
void round_robin(struct Process processes[], int n, int quantum) {
    // Variables to keep track of current time and total waiting time
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int completed_processes = 0;

    // Array to keep track of completion status of processes
    int is_completed[n];
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        processes[i].remaining_burst = processes[i].burst;
    }

    // Variable to track current process ID for Gantt chart
    int current_process = -1;

    // Print the initial part of the Gantt chart
    printf("\nGantt Chart:\n");
    printf("0");

    // Process each job in Round Robin order
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_burst > 0 && !is_completed[i]) {
                int time_slice = (processes[i].remaining_burst <= quantum) ? processes[i].remaining_burst : quantum;

                // Print Gantt chart when process changes
                if (current_process != processes[i].pid) {
                    if (current_process != -1) { // Not the very first process
                        printf("----%d", current_process);
                    }
                    current_process = processes[i].pid;
                }

                // Update time and remaining burst
                current_time += time_slice;
                processes[i].remaining_burst -= time_slice;

                if (processes[i].remaining_burst == 0) {
                    processes[i].completion = current_time;
                    processes[i].turnaround = processes[i].completion - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;

                    // Accumulate total waiting and turnaround times
                    total_waiting_time += processes[i].waiting;
                    total_turnaround_time += processes[i].turnaround;

                    // Mark process as completed
                    is_completed[i] = 1;
                    completed_processes++;
                }
            }
        }
    }

    // Print final part of the Gantt chart
    printf("----%d\n", current_process);

    // Calculate average waiting time and average turnaround time
    float average_waiting_time = (float) total_waiting_time / n;
    float average_turnaround_time = (float) total_turnaround_time / n;

    // Print results
    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival, processes[i].burst, processes[i].waiting, processes[i].turnaround, processes[i].completion);
    }
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
}

int main() {
    int n, quantum;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Array of processes
    struct Process processes[n];

    // Input arrival and burst times for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
    }

    // Input quantum for Round Robin
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Perform Round Robin scheduling
    round_robin(processes, n, quantum);

    return 0;
}
