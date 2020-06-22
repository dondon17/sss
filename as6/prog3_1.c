/***************************************************************************
 *  실습과제 6 - 공유 메모리 사용(세마포어로 동기화 o)
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog3_1.c
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

// 세마포 값을 1 감소시키면서 세마포를 획득
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

// 세마포 값을 1 증가시키면서 세마포 해제
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
    union semun{
        int val;
        struct semid_ds *buf;
        unsigned short int *array;
    }semarg;
    
    // 공유메모리와 세마포어의 키 설정
    key_t shmkey = ftok("myshm", 1);
    key_t semkey = ftok("mysem", 1);

    // 세마포어 생성 및 초기화
    if((semid = semget(semkey, 1, IPC_CREAT|0666)) == -1){
        perror("semget");
        exit(1);
    }
    semarg.val = 1; // 세마포의 값을 1로 설정(세마포를 하나의 프로세스만 잡을 수 있도록)
    if(semctl(semid, 0, SETVAL, semarg) == -1){
        perror("semctl");
        exit(1);
    }

    // 공유 메모리 생성 및 연결
    if((shmid = shmget(shmkey, 1024, IPC_CREAT|0666)) == -1){
        perror("shmid");
        exit(1);
    }
    shmaddr = shmat(shmid, NULL, 0);

    for(int i=0; i<10; i++){
        p(semid); // 세마포어 획득
        strcpy(shmaddr, "Semaphore");
        strcpy(buf, shmaddr);
        printf("A : %s\n", buf);
        sleep(1);
        v(semid); // 세마포어 해제
    }
    
    // 공유 메모리 해제
    shmdt(shmaddr);

    // 공유메모리와 세마포어를 제거하지 않는 이유는 아직 다른 프로세스에서 접근하고 있을 수 있기 때문
    return 0;
}