#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<signal.h>

#define SIZE 1024

int shmid;

int main(void){
    key_t key;
    void *shmaddr;
    
    key = ftok("myshm", 1);
    if((shmid = shmget(key, SIZE, 0)) == -1){
        perror("create shared memory failed...\n");
        exit(1);
    }

    if((shmaddr = shmat(shmid, NULL, 0)) == (void*)-1){
        perror("shmat failed...\n");
        exit(1);
    }

    for(int i=0; i<10; i++){
        strcpy(shmaddr, "Prog");

        printf("B : %s\n", (char*)shmaddr);
        sleep(1);
    }
    if(shmdt(shmaddr) == -1){
        perror("shmdt");
        exit(1);
    }

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}