/***************************************************************************
 *  정리과제 - pthread mutex
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: mutex.c
 *  작성일: 2020 / 06 / 03
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int shared_count = 0; // 두 쓰레드에서 공유할 변수
pthread_mutex_t mutex_lock; // 잠금 기능으로 사용할 mutex lock 선언

void* func(void *arg){
    char* thname = (char*)arg;
    // 공유 자원에 대해 작업할 때 mutex lock을 잡고 수행
    pthread_mutex_lock(&mutex_lock);
    for(int i=1; i<=10; i++){
        printf("%s:  shared count value: %d\n", thname, shared_count);
        shared_count++;
        sleep(1);
    }
    // 공유 자원에 대한 작업을 끝마치면 잡고 있던 mutex lock 해제
    pthread_mutex_unlock(&mutex_lock);
    pthread_exit(0);
}

int main(int argc, char** argv){
    int err;
    int tret;
    pthread_t t1, t2;

    // mutex lock 초기화
    pthread_mutex_init(&mutex_lock, NULL);

    if((err = pthread_create(&t1, NULL, func, (void*)"thread 1")) != 0){
        printf("fail to create thread 1 : %s\n", strerror(err));
        exit(0);
    }
    if((err = pthread_create(&t2, NULL, func, (void*)"thread 2")) != 0){
        printf("fail to create thread 2 : %s\n", strerror(err));
        exit(0);
    }

    pthread_join(t1, (void*)&tret);
    pthread_join(t2, (void*)&tret);
    
    // mutex lock 폐기
    pthread_mutex_destroy(&mutex_lock);
    return 0;
}