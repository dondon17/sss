/***************************************************************************
 *  실습과제 6 - 공유 메모리 사용(동기화 x)
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog2_2.c
 *  작성일: 2020 / 06 / 02
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
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
    char buf[1024];

    // prog2_1.c에서 생성된 공유 메모리의 키 값으로 해당 공유 메모리에 접근
    key = ftok("myshm", 1);
    if((shmid = shmget(key, SIZE, 0)) == -1){
        perror("create shared memory failed...\n");
        exit(1);
    }
    // 자신의 메모리 영역과 공유 메모리 영역을 연결
    if((shmaddr = shmat(shmid, NULL, 0)) == (void*)-1){
        perror("shmat failed...\n");
        exit(1);
    }

    // 공유 메모리에 작업 수행
    for(int i=0; i<10; i++){
        strcpy(shmaddr, "Prog"); // 공유 메모리에 쓰기 작업
        strcpy(buf, shmaddr); // 공유 메모리로부터 읽기 작업
        printf("B : %s\n", buf);
        sleep(1);
    }
    // 자신의 메모리 영역으로부터 공유 메모리 해제
    if(shmdt(shmaddr) == -1){
        perror("shmdt");
        exit(1);
    }

    return 0;
}