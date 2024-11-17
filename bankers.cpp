#include <iostream>
using namespace std;

// Global variables
int n = 5;  // number of processes
struct abc {
    int a;  // Resource A
    int b;  // Resource B
    int c;  // Resource C
};

// Define structures to hold resource information
abc allocation[5];
abc maxi[5];
abc available;
abc remain[5];
abc total;

// Function to gather input
void input() {
    cout << "Enter the allocation of each process (a, b, c) resources allocated:" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> allocation[i].a >> allocation[i].b >> allocation[i].c;
    }

    cout << "Enter the max needed allocation of each process (a, b, c) resources allocated:" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> maxi[i].a >> maxi[i].b >> maxi[i].c;
    }

    cout << "Enter the total available resources (a, b, c): ";
    cin >> total.a >> total.b >> total.c;

    // Calculate remaining needs for each process
    for (int i = 0; i < 5; i++) {
        remain[i].a = maxi[i].a - allocation[i].a;
        remain[i].b = maxi[i].b - allocation[i].b;
        remain[i].c = maxi[i].c - allocation[i].c;
    }

    // Calculate the currently available resources
    int totalAllocatedA = 0, totalAllocatedB = 0, totalAllocatedC = 0;
    for (int i = 0; i < 5; i++) {
        totalAllocatedA += allocation[i].a;
        totalAllocatedB += allocation[i].b;
        totalAllocatedC += allocation[i].c;
    }

    available.a = total.a - totalAllocatedA;
    available.b = total.b - totalAllocatedB;
    available.c = total.c - totalAllocatedC;
}

// Function to check if the system is in a safe state
bool isSafeState() {
    bool finish[5] = {false};  // Track if each process can finish
    abc work = available;  // Copy of available resources to simulate allocations
    int safeSequence[5];  // Store the safe sequence if it exists
    int count = 0;  // Number of processes that can safely finish

    while (count < n) {
        bool foundProcess = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i] && 
                remain[i].a <= work.a &&
                remain[i].b <= work.b &&
                remain[i].c <= work.c) {

                // Simulate allocation by adding allocated resources of process i
                work.a += allocation[i].a;
                work.b += allocation[i].b;
                work.c += allocation[i].c;

                safeSequence[count++] = i;  // Add process i to the safe sequence
                finish[i] = true;
                foundProcess = true;
            }
        }

        if (!foundProcess) {
            // No process could safely finish in this pass, so the system is not in a safe state
            return false;
        }
    }

    // Print the safe sequence if the system is in a safe state
    cout << "The system is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSequence[i] << " ";
    }
    cout << endl;

    return true;
}

int main() {
    input();

    // Check if the system is in a safe state
    if (isSafeState()) {
        cout << "Safe state confirmed." << endl;
    } else {
        cout << "The system is not in a safe state. Deadlock may occur." << endl;
    }

    return 0;
}
