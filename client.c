#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(){
    key_t key=ftok("server.c",66); //unique key same as server

    //attach to the shared memory
    int shmid=shmget(key,1024,0666|IPC_CREAT);
    char *str=(char*)shmat(shmid,NULL,0);

    //Read from shared memory
    printf("Client is Reading");
    printf("\nClient : %s \n ",str);

    shmdt(str);
    return 0;
}