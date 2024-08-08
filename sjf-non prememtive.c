#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completion; // Completion time
};

// Function to compare processes by arrival time
int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    return p1->arrival - p2->arrival;
}

// Function to perform SJF scheduling and print Gantt chart
void sjf(struct Process processes[], int n) {
    int current_time = 0;
    int total_waiting_time = 0;

    // Array to keep track of completion order
    int completion_order[n];

    // Initialize process data
    for (int i = 0; i < n; i++) {
        processes[i].waiting = 0;
        processes[i].turnaround = 0;
        processes[i].completion = 0;
    }

    // Sort processes by arrival time
    qsort(processes, n, sizeof(struct Process), compare);

    int gantt_time_stamps[1000];
    int gantt_processes[1000];
    int gantt_count = 0;

    int remaining_processes = n;
    int finished[n];
    for (int i = 0; i < n; i++) {
        finished[i] = 0;
    }

    int last_time = 0;

    while (remaining_processes > 0) {
        int shortest_index = -1;
        int shortest_burst = INT_MAX;

        // Find the shortest job that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && finished[i] == 0 &&
                processes[i].burst < shortest_burst) {
                shortest_index = i;
                shortest_burst = processes[i].burst;
            }
        }

        if (shortest_index == -1) {
            // No process is ready to execute, move time forward to next arrival
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival > current_time && processes[i].arrival < next_arrival) {
                    next_arrival = processes[i].arrival;
                }
            }
            if (next_arrival != INT_MAX) {
                if (current_time < next_arrival) {
                    // Record idle time
                    if (last_time != current_time) {
                        gantt_time_stamps[gantt_count] = current_time;
                        gantt_processes[gantt_count] = -1; // Idle slot in Gantt chart
                        gantt_count++;
                        last_time = current_time;
                    }
                    current_time = next_arrival;
                }
            }
        } else {
            // Execute the shortest job
            if (current_time < processes[shortest_index].arrival) {
                // Record idle time
                if (last_time != current_time) {
                    gantt_time_stamps[gantt_count] = current_time;
                    gantt_processes[gantt_count] = -1; // Idle slot in Gantt chart
                    gantt_count++;
                    last_time = current_time;
                }
                current_time = processes[shortest_index].arrival;
            }

            // Record the start time of the process
            if (last_time != current_time) {
                gantt_time_stamps[gantt_count] = current_time;
                gantt_processes[gantt_count] = processes[shortest_index].pid;
                gantt_count++;
                last_time = current_time;
            }

            current_time += processes[shortest_index].burst;
            processes[shortest_index].waiting = current_time - processes[shortest_index].arrival - processes[shortest_index].burst;
            processes[shortest_index].turnaround = current_time - processes[shortest_index].arrival;
            processes[shortest_index].completion = current_time;
            total_waiting_time += processes[shortest_index].waiting;
            completion_order[n - remaining_processes] = processes[shortest_index].pid;
            finished[shortest_index] = 1;
            remaining_processes--;
        }
    }

    // Calculate average waiting time
    float average_waiting_time = (float)total_waiting_time / n;

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    printf("Time: ");
    for (int i = 0; i < gantt_count; i++) {
        printf(" %4d", gantt_time_stamps[i]);
    }
    printf(" %4d\n", current_time);

    printf("       ");
    for (int i = 0; i < gantt_count; i++) {
        if (gantt_processes[i] == -1) {
            printf("| Idle ");
        } else {
            printf("| P%d ", gantt_processes[i]);
        }
    }
    printf("|\n");

    // Print waiting time, turnaround time, and completion time
    printf("\nProcess Scheduling Information:\n");
    printf("PID\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].waiting, processes[i].turnaround, processes[i].completion);
    }
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
}

int main() {
    int n;

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

    // Perform SJF scheduling and print Gantt chart
    sjf(processes, n);

    return 0;
}
