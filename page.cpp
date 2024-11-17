#include <iostream>
using namespace std;

int ns;
int nf;
int str[20];
int nfaults;
int nhits;

void input() {
    cout << "Enter number of input pages: ";
    cin >> ns;
    cout << "Enter the page reference string: ";
    for (int i = 0; i < ns; i++) {
        cin >> str[i];
    }
    cout << "Enter number of frames: ";
    cin >> nf;
}

void fifo() {
    int index = 0;
    int frames[nf];
    for (int i = 0; i < nf; i++) {
        frames[i] = -1;
    }
    nfaults = 0;
    nhits = 0;
    
    for (int i = 0; i < ns; i++) {
        bool hit = false;
        int target = str[i];
        
        for (int j = 0; j < nf; j++) {
            if (frames[j] == target) {
                nhits++;
                hit = true;
                break;
            }
        }
        
        if (!hit) { // if not a hit
            nfaults++;
            frames[index] = target;
            index = (index + 1) % nf;
        }
    }
    
    cout << "FIFO - Hits: " << nhits << ", Faults: " << nfaults << endl;
}

void lru() {
    int frames[nf];
    int lused[nf];
    for (int i = 0; i < nf; i++) {
        frames[i] = -1;
        lused[i] = 0;
    }
    
    nfaults = 0;
    nhits = 0;
    
    for (int i = 0; i < ns; i++) {
        int target = str[i];
        bool hit = false;
        
        for (int j = 0; j < nf; j++) {
            if (target == frames[j]) {
                nhits++;
                lused[j] = i;
                hit = true;
                break;
            }
        }
        
        if (!hit) { // if not a hit
            nfaults++;
            int index = 0;
            for (int j = 1; j < nf; j++) {
                if (lused[j] < lused[index]) {
                    index = j;
                }
            }
            frames[index] = target;
            lused[index] = i;
        }
    }
    
    cout << "LRU - Hits: " << nhits << ", Faults: " << nfaults << endl;
}

int latest(int a, int b) {
    for (int i = a; i < ns; i++) {
        if (str[i] == b) {
            return i;
        }
    }
    return ns + 1;  // Return a large value if the page won’t appear again
}

void optimal() {
    int frames[nf];
    int fuse[nf];
    for (int i = 0; i < nf; i++) {
        frames[i] = -1;
        fuse[i] = ns + 1;
    }
    
    nfaults = 0;
    nhits = 0;
    
    for (int i = 0; i < ns; i++) {
        int target = str[i];
        bool hit = false;
        
        for (int j = 0; j < nf; j++) {
            if (target == frames[j]) {
                nhits++;
                fuse[j] = latest(i + 1, target);
                hit = true;
                break;
            }
        }
        
        if (!hit) { // if not a hit
            nfaults++;
            int index = 0;
            for (int j = 1; j < nf; j++) {
                if (fuse[j] > fuse[index]) {
                    index = j;
                }
            }
            frames[index] = target;
            fuse[index] = latest(i + 1, target);
        }
    }
    
    cout << "Optimal - Hits: " << nhits << ", Faults: " << nfaults << endl;
}

int main() {
    int choice;
    
    while (true) {
        cout << "\nPage Replacement Algorithms Menu:\n";
        cout << "1. Input Page Reference String and Frames\n";
        cout << "2. FIFO Page Replacement\n";
        cout << "3. LRU Page Replacement\n";
        cout << "4. Optimal Page Replacement\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                input();
                break;
            case 2:
                fifo();
                break;
            case 3:
                lru();
                break;
            case 4:
                optimal();
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
