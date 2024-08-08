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

// Function to perform FCFS scheduling and print Gantt chart
void fcfs_scheduling(struct Process processes[], int n) {
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

    // Sort processes by arrival time
    qsort(processes, n, sizeof(struct Process), compare);

    int gantt_time_stamps[1000];
    int gantt_processes[1000];
    int gantt_count = 0;

    // Perform FCFS scheduling
    for (int i = 0; i < n; i++) {
        // Calculate waiting time and turnaround time
        if (current_time < processes[i].arrival) {
            if (gantt_count > 0 && gantt_processes[gantt_count - 1] == -1) {
                gantt_time_stamps[gantt_count - 1] = processes[i].arrival;
            } else {
                gantt_time_stamps[gantt_count] = processes[i].arrival;
                gantt_processes[gantt_count] = -1; // Idle slot in Gantt chart
                gantt_count++;
            }
            current_time = processes[i].arrival;
        }

        gantt_time_stamps[gantt_count] = current_time + processes[i].burst;
        gantt_processes[gantt_count] = processes[i].pid;
        gantt_count++;

        processes[i].waiting = current_time - processes[i].arrival;
        current_time += processes[i].burst;
        processes[i].turnaround = current_time - processes[i].arrival;
        processes[i].completion = current_time;
        total_waiting_time += processes[i].waiting;
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

    // Input arrival, burst times for each process
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
    }

    // Perform FCFS scheduling and print Gantt chart
    fcfs_scheduling(processes, n);

    return 0;
}
