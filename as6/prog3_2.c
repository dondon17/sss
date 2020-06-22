/***************************************************************************
 *  실습과제 6 - 공유 메모리 사용(세마포어로 동기화 o)
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog3_2.c
 *  작성일: 2020 / 06 / 02
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/types.h>

// 세마포 값을 1 감소하면서 세마포 획득
void p(int semid){
    struct sembuf pbuf;
    pbuf.sem_num = 0;
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;
    if(semop(semid, &pbuf, 1) == -1){
        perror("semop");
        exit(1);
    }
}

// 세마포 값을 1 증가시킴으로써 세마포를 해제
void v(int semid){
    struct sembuf vbuf;
    vbuf.sem_num = 0;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;
    if(semop(semid, &vbuf, 1) == -1){
        perror("semop");
        exit(1);
    }
}

int main(void){
    int shmid;
    int semid;
    void* shmaddr;
    char buf[1024];

    // 생성된 공유메모리와 세마포에 접근하기 위한 키
    key_t shmkey = ftok("myshm", 1);
    key_t semkey = ftok("mysem", 1);

    // 해당 키를 통해 공유 메모리 접근 및 자신의 메모리 영역에 연결
    if((shmid = shmget(shmkey, 1024, 0)) == -1){
        perror("shmid");
        exit(1);
    }
    shmaddr = shmat(shmid, NULL, 0);

    // 해당 키를 이용해 세마포어 접근
    if((semid = semget(semkey, 0, 0)) == -1){
        perror("semget");
        exit(1);
    }

    for(int i=0; i<10; i++){
        p(semid); // 세마포어 획득
        strcpy(shmaddr, "prog"); // 공유 메모리에 쓰기
        strcpy(buf, shmaddr); // 공유 메모리로부터 읽기
        printf("B : %s\n", buf);
        sleep(1);
        v(semid); // 세마포어 해제
    }

    shmdt(shmaddr); // 공유 메모리 해제(삭제가 아님)

    // 마찬가지로 다른 프로세스에서 작업중일 수도 있기에 공유 메모리와 세마포어를 제거하지 않음

    return 0;
}