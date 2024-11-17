//We have to code for cpu shedule using two algorithms SJF premptive and rr

#include<iostream>
using namespace std;

//gloabl variables
struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int rbt;
    int tat;
    int wt;
};
int n;
process p[10];
int tq;

void input(){
    cout<<"Enter the number of the process"<<endl;
    cin>>n;

    cout<<"Enter the arrival tiume and burst time opf each process "<<endl;
    for(int i=0;i<n;i++){
        p[i].pid=i;
        cin>>p[i].at;
        cin>>p[i].bt;
    }
}

//function to shedule in sjf premptive
void sjf(){
    cout<<"In SJF";
}

//function to shedule in rr
void rr(){
    cout<<"Enter the time quanta"<<endl;
    cin>>tq;
    
}

void show(){
    cout<<"PID\tAT\tBT"<<endl;
    for(int i=0;i<n;i++)
        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<endl;
}

//function to show the menu
void menu(){
    int choice=0;
    while(1){
    cout<<"Enter \n1 for SJF(Premptive) \n2 for RR \n-1 to exit"<<endl;
    cin>>choice;
    
    if(choice==1){
        sjf();
    }

    else if(choice==2){
        rr();
    }

    else if(choice == -1){return;}
    }
}

int main(){
    input();
    show();
    menu();
    return 0;
} 