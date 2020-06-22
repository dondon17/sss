/***************************************************************************
 *  실습과제 6 - 공유 메모리 사용(동기화 x)
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog2_1.c
 *  작성일: 2020 / 06 / 02
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
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
    char buf[1024];
    
    key = ftok("myshm", 1);
    // 키를 지정하고 해당 키 값을 갖는 공유 메모리 생성
    if((shmid = shmget(key, SIZE, IPC_CREAT|0666)) == -1){
        perror("create shared memory failed...\n");
        exit(1);
    }

    // 공유 메모리를 자신의 메모리 영역으로 첨부(연결)
    if((shmaddr = shmat(shmid, (void*)0, 0)) == (void*)-1){
        perror("shmat failed...\n");
        exit(1);
    }

    // 공유 메모리에 데이터(문자열)를 쓰고, 공유메모리로부터 데이터를 읽어와 출력
    for(int i=0; i<10; i++){
        strcpy(shmaddr, "System");
        strcpy(buf, shmaddr);
        printf("A : %s\n", buf);
        sleep(1);
    }
    
    // 공유 메모리를 자신의 메모리 영역으로부터 해제
    if(shmdt(shmaddr) == -1){
        perror("shmdt");
        exit(1);
    }

    return 0;
}