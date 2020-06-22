/***************************************************************************
 *  정리과제 - pthread condition variable
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: condvar.c
 *  작성일: 2020 / 06 / 03
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int gloval = 0; // 쓰레드에서 접근할 공유변수
int flag = 0; // 쓰레드를 대기시킬지 깨울지를 정하는 flag 비트

pthread_mutex_t mulock = PTHREAD_MUTEX_INITIALIZER; // 사용할 mutex 선언
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // 조건변수로 사용할 변수 선언

void* func1(void* argv){
    while(1){
        pthread_mutex_lock(&mulock); // mutex lock 잠금
        if(gloval%2 ==0){
            printf("%s : gloval = %d\n", (char*)argv, gloval);
            gloval++;
            sleep(1);
        }   
        flag = 1;
        pthread_cond_signal(&cond); // cond 조건 변수를 가지고 있는 프로세스 깨움
        pthread_cond_wait(&cond, &mulock); // 자신은 대기상태로 돌입
        pthread_mutex_unlock(&mulock); // mutex lock 해제
    }
    return NULL;
}

void* func2(void* argv){
    while(1){
        pthread_mutex_lock(&mulock);
        // flag비트가 0이면 계속 대기
        while(flag==0) pthread_cond_wait(&cond, &mulock); 
        // flag 비트가 1이 되면 자신의 작업 수행
        if(gloval%2 == 1){
            printf("%s : gloval = %d\n", (char*)argv, gloval);
            gloval++;
            sleep(1);
        }
        // 작업을 마치고 다시 flag 비트를 0으로 설정한뒤 대기상태의 쓰레드를 깨움
        flag = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mulock); // mutex lock 해제
    }
    return NULL;
}

int main(int argc, char **argv){
    int err;
    pthread_t t1, t2;
    int status;

    if((err = pthread_create(&t1, NULL, func1, (char*)"thread 1")) != 0){
        printf("failed to create thread1 : %s\n", strerror(err));
        exit(0);
    }
    if((err = pthread_create(&t2, NULL, func2, (char*)"thread 2")) != 0){
        printf("failed to create thread2 : %s\n", strerror(err));
        exit(0);
    }

    pthread_join(t1, (void**)&status);
    pthread_join(t2, (void**)&status);

    return 0;
}