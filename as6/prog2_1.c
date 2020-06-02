#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<signal.h>
#include<sys/shm.h>

#define SIZE 1024
int shmid;

int main(void){

    key_t key;
    void *shmaddr;

    key = ftok("myshm", 1);
    // 1. 키 1111의 공유 메모리 생성 - 이미 키 1111의 공유메모리가 있는 경우, 해당 공유메모리에 접근
    if((shmid = shmget(key, SIZE, IPC_CREAT|0666)) == -1){
        perror("create shared memory failed...\n");
        exit(1);
    }

    // 2. 공유 메모리를 호출한 프로세스의 메모리 영역으로 첨부
    if((shmaddr = shmat(shmid, (void*)0, 0)) == (void*)-1){
        perror("shmat failed...\n");
        exit(1);
    }

    // 3. 공유 메모리에 데이터(문자열)를 쓰고, 공유메모리에서 읽어와 출력
    for(int i=0; i<10; i++){
        strcpy(shmaddr, "System");
        printf("A : %s\n", (char*)shmaddr);
        sleep(1);
    }
    
    // 4. 공유 메모리를 호출한 프로세스의 메모리 영역에서 해제
    if(shmdt(shmaddr) == -1){
        perror("shmdt");
        exit(1);
    }

    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}