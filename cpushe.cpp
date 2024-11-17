//write code for cpu sheduling for sjf,rr

#include<iostream>
#include<vector>
using namespace std;

struct Process{
    int id,arrival,burst,remaining,completion,wait,turnaround;
};
int n,qua;
vector<Process>p(n);

void gc(vector<int>&gantt_chart){
    cout<<"Gantt Chart:\n";
    for (int id : gantt_chart) {
        if (id == -1)
            cout << " Idle |";
        else
            cout << " P" << id << " |";
    }  
}    

void SJF(){
    int time=0,completed=0,shortest;
    float total_wait=0,total_turnaround=0;
    vector<int>gantt_chart;

    while(completed<n){
        shortest=-1;
        for(int i=0;i<n;i++){
            if(p[i].arrival<=time && p[i].remaining>0 && (shortest==-1 || p[i].remaining<p[shortest].remaining))
                shortest=i;
        }

        if(shortest ==-1 ){time++;continue;}

        p[shortest].remaining--;
        gantt_chart.push_back(p[shortest].id);
        time++;
        if (p[shortest].remaining == 0) {
            completed++;
            p[shortest].completion = time;
            p[shortest].turnaround = time - p[shortest].arrival;
            p[shortest].wait = p[shortest].turnaround - p[shortest].burst;
            total_wait += p[shortest].wait;
            total_turnaround += p[shortest].turnaround;
        }
    }
    cout<<"SJF\nPID\tArr\tBurst\tComp\tWait\tTurn\n";
    for (int i = 0; i < n; i++)
        cout << p[i].id << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].completion << "\t" << p[i].wait << "\t" << p[i].turnaround << "\n";

    cout << "Avg Wait Time: " << total_wait / n << ", Avg Turnaround Time: " << total_turnaround / n << "\n";
    gc( gantt_chart );
}

void roundrobin(){
    int time=0,completed=0;
    float total_wait=0,total_turnaround=0;
    vector<int> gantt_chart;

    while(completed<n){
        bool idle=true;
        for(int i=0;i<n;i++){
            if(p[i].arrival<=time && p[i].remaining>0){
                idle=false;
                int exec_time = (p[i].remaining > qua) ? qua : p[i].remaining;
                p[i].remaining=p[i].remaining-exec_time;
                for(int j=0;j<exec_time;j++)
                    gantt_chart.push_back(p[i].id);

                time+=exec_time;

                if (p[i].remaining == 0) {
                    p[i].completion = time;
                    p[i].turnaround = time - p[i].arrival;
                    p[i].wait = p[i].turnaround - p[i].burst;
                    total_wait += p[i].wait;
                    total_turnaround += p[i].turnaround;
                    completed++;
                }   
            }
             if (idle) {
            gantt_chart.push_back(-1); // Mark idle time in Gantt chart
            time++;
            }
        }
    }
    cout << "\nRound Robin:\nPID\tArr\tBurst\tComp\tWait\tTurn\n";
    for (int i = 0; i < n; i++)
        cout << p[i].id << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].completion << "\t" << p[i].wait << "\t" << p[i].turnaround << "\n";

    cout << "Avg Wait Time: " << total_wait / n << ", Avg Turnaround Time: " << total_turnaround / n << "\n";
    gc( gantt_chart );
}


void input(){
    cout<<"Enter the number of processes"<<endl;
    cin>>n;
    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter arrival and burst time for P" << i + 1 << ": ";
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
    }
    cout << "Enter time quantum for Round Robin: ";
    cin >> qua;
}

int main(){
    input();
    SJF();
    roundrobin();
    return 0;
}