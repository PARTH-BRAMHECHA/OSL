#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Priority
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
    int completion; // Completion time
};

// Function to compare processes by arrival time, and by priority if arrival times are the same
int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    if (p1->arrival != p2->arrival)
        return p1->arrival - p2->arrival;
    return p1->priority - p2->priority;
}

// Function to perform Priority scheduling and print Gantt chart
void priority_scheduling(struct Process processes[], int n) {
    int current_time = 0;
    int total_waiting_time = 0;
    int gantt_chart[1000];
    int gantt_index = 0;

    // Initialize process data
    for (int i = 0; i < n; i++) {
        processes[i].waiting = 0;
        processes[i].turnaround = 0;
        processes[i].completion = 0;
    }

    // Sort processes by arrival time and priority if arrival times are the same
    qsort(processes, n, sizeof(struct Process), compare);

    // Array to keep track of whether a process has been executed
    int executed[n];
    for (int i = 0; i < n; i++) {
        executed[i] = 0;
    }

    int remaining_processes = n;
    int gantt_time_stamps[1000];
    int gantt_processes[1000];
    int gantt_count = 0;

    while (remaining_processes > 0) {
        int highest_priority_index = -1;

        // Find the process with the highest priority that has arrived and not yet executed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && executed[i] == 0) {
                if (highest_priority_index == -1 || processes[i].priority < processes[highest_priority_index].priority) {
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1) {
            // No process is ready to execute, move time forward to the next arrival
            int next_arrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival > current_time && processes[i].arrival < next_arrival) {
                    next_arrival = processes[i].arrival;
                }
            }
            if (next_arrival != INT_MAX) {
                if (gantt_count > 0 && gantt_processes[gantt_count - 1] == -1) {
                    gantt_time_stamps[gantt_count - 1] = next_arrival;
                } else {
                    gantt_time_stamps[gantt_count] = next_arrival;
                    gantt_processes[gantt_count] = -1; // Idle slot in Gantt chart
                    gantt_count++;
                }
                current_time = next_arrival;
            }
        } else {
            // Execute the highest priority job
            if (gantt_count > 0 && gantt_processes[gantt_count - 1] == processes[highest_priority_index].pid) {
                gantt_time_stamps[gantt_count - 1] = current_time + processes[highest_priority_index].burst;
            } else {
                gantt_time_stamps[gantt_count] = current_time + processes[highest_priority_index].burst;
                gantt_processes[gantt_count] = processes[highest_priority_index].pid;
                gantt_count++;
            }

            processes[highest_priority_index].waiting = current_time - processes[highest_priority_index].arrival;
            current_time += processes[highest_priority_index].burst;
            processes[highest_priority_index].turnaround = current_time - processes[highest_priority_index].arrival;
            processes[highest_priority_index].completion = current_time;
            total_waiting_time += processes[highest_priority_index].waiting;
            executed[highest_priority_index] = 1;
            remaining_processes--;
        }
    }

    // Calculate average waiting time
    float average_waiting_time = (float)total_waiting_time / n;

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    printf("Time: ");
    for (int i = 0; i < gantt_count; i++) {
        if (gantt_processes[i] == -1) {
            printf("| Idle ");
        } else {
            printf("| P%d ", gantt_processes[i]);
        }
    }
    printf("|\n");

    printf("       ");
    for (int i = 0; i < gantt_count; i++) {
        printf(" %4d", gantt_time_stamps[i]);
    }
    printf("\n");

    // Print completion order, waiting time, turnaround time, and completion time
    printf("\nCompletion Order for Priority Scheduling:\n");
    printf("PID\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, processes[i].waiting, processes[i].turnaround, processes[i].completion);
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

    // Input arrival, burst times, and priority for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
        printf("Enter priority for process %d (lower number means higher priority): ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Perform Priority scheduling and print Gantt chart
    priority_scheduling(processes, n);

    return 0;
}
