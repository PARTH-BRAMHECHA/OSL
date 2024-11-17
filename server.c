#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(){
    key_t key=ftok("server.c",66);

    //create shared memory
    int shmid=shmget(key,1024,0666|IPC_CREAT);

    //Attach to shared memory
    char *str=(char*)shmat(shmid,NULL,0);

    //write to memory
    printf("Server: Enter a Message\n");
    fgets(str,1024,stdin);
    printf("Server: Message has been written\n");

    //Detach memmory
    shmdt(str);
    return 0;
}