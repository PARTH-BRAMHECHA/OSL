#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

// Global variables
int n;
int track[20];
int st;

// Function to input data
void input() {
    cout << "Enter the number of inputs: ";
    cin >> n;
    cout << "Enter the requested track: ";
    for (int i = 0; i < n; i++) {
        cin >> track[i];
    }
    cout << "Enter the initial track: ";
    cin >> st;
}

// SSJF algorithm
void ssjf(int track[], int n, int st) {
    int temp[20];
    for (int i = 0; i < n; i++)
        temp[i] = track[i];

    sort(temp, temp + n);

    int visited[n];
    fill(visited, visited + n, -1);

    int j;
    for (j = 0; j < n; j++) {
        if (temp[j] == st)
            break;
    }

    visited[j] = 1;
    int comp = 1;  // Start point is already visited
    int curr = j;

    cout << "SSJF Order: " << temp[curr] << " ";

    while (comp < n) {
        int l = curr - 1;
        int m = curr + 1;

        // Find the next unvisited track in both directions
        while (l >= 0 && visited[l] != -1) l--;
        while (m < n && visited[m] != -1) m++;

        int a = (l >= 0) ? abs(temp[l] - temp[curr]) : INT_MAX;
        int b = (m < n) ? abs(temp[m] - temp[curr]) : INT_MAX;

        if (a < b) {
            visited[l] = 1;
            curr = l;
        } else {
            visited[m] = 1;
            curr = m;
        }

        cout << temp[curr] << " ";
        comp++;
    }
    cout << endl;
}

// SCAN algorithm
void scan() {
    int temp[22];  // Increased size to handle extra elements
    for (int i = 0; i < n; i++)
        temp[i] = track[i];

    cout << "Enter 0 for moving downwards, 1 for moving upwards: ";
    int ch;
    cin >> ch;

    if (ch == 0) {
        temp[n] = 0;
    } else {
        temp[n] = 199;
    }
    temp[n + 1] = st;
    sort(temp, temp + n + 2);

    int j;
    for (j = 0; j < n + 2; j++) {
        if (temp[j] == st)
            break;
    }

    cout << "SCAN Order: ";
    if (ch == 0) {
        for (int i = j; i >= 0; i--)
            cout << temp[i] << " ";
        for (int i = j + 1; i < n + 2; i++)
            cout << temp[i] << " ";
    } else {
        for (int i = j; i < n + 2; i++)
            cout << temp[i] << " ";
        for (int i = j - 1; i >= 0; i--)
            cout << temp[i] << " ";
    }
    cout << endl;
}

// C-LOOK algorithm
void clook() {
    int temp[21];  // Increased size for extra element
    for (int i = 0; i < n; i++)
        temp[i] = track[i];

    cout << "Enter 0 for moving downwards, 1 for moving upwards: ";
    int ch;
    cin >> ch;

    temp[n] = st;
    sort(temp, temp + n + 1);

    int j;
    for (j = 0; j < n + 1; j++) {
        if (temp[j] == st)
            break;
    }

    cout << "C-LOOK Order: ";
    if (ch == 0) {
        for (int i = j; i >= 0; i--)
            cout << temp[i] << " ";
        for (int i = n; i > j; i--)
            cout << temp[i] << " ";
    } else {
        for (int i = j; i < n + 1; i++)
            cout << temp[i] << " ";
        for (int i = 0; i < j; i++)
            cout << temp[i] << " ";
    }
    cout << endl;
}

// Main function to select and run an algorithm
int main() {
    input();
    int choice;
    cout << "Choose a scheduling algorithm:\n";
    cout << "1. SSJF\n2. SCAN\n3. C-LOOK\nChoice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            ssjf(track, n, st);
            break;
        case 2:
            scan();
            break;
        case 3:
            clook();
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
