/***************************************************************************
 *  실습과제 5 - 쓰레도 동기화 프로그램(mutex lock, 조건 변수 관련 함수 사용)
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog1.c
 *  작성일: 2020 / 05 / 15
 *  마감일: 2020 / 05 / 21
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

int count = 1;
int flag = 0;

// 각 func1, func2의 인자로 전달해줄 문구 선언 및 초기화
const char* t1 = "function1";   
const char* t2 = "function2";

// mutex 객체 선언
pthread_mutex_t mutex;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *func1(void *data){
    while(1){
        // thread1에서 먼저 mutex lock을 선점
        pthread_mutex_lock(&mutex);
        // count값의 범위에 따라 아래 조건문 수행
        if(count < 4){
            printf("[By %s] count value: %d\n", (char*)data, count);
            count++;
        }
        if(count > 7 && count < 11){
            printf("[By %s] count value: %d\n", (char*)data, count);
            count++;
        }
        // func2에서 작업을 수행할지 말지를 결정하기 위해 flag비트 설정
        flag = 1;
        // wait중인 func2를 깨우고 자신은 wait상태로 들어가면서 lock을 해제
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}
void *func2(void *data){
    while(1){
        // func2에서 lock 소유
        pthread_mutex_lock(&mutex);
        // flag 비트가 0인 경우에는 계속 wait상태로 대기
        while(flag == 0){
            pthread_cond_wait(&cond, &mutex);
        }

        // flag 비트가 1로 변경된 경우 아래 count범위에 대한 조건문 수행
        if(count > 11) break;
        if(count > 3 && count < 8){
            printf("[By %s] count value: %d\n", (char*)data, count);
            count++;
        }
        if(count > 10){
            printf("[By %s] count value: %d\n", (char*)data, count);
            count++;
        }

        // func2는 count가 자신이 수행하는 범위 내인 경우 count값을 출력한 뒤 증가시키고
        // flag = 0으로 설정해 다시 자신이 락을 잡을 수 있을 때까지 대기
        flag = 0;
        
        // wait중인 func1을 깨우고 잡고 있던 mutex lock을 해제
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char **argv){
    pthread_t thr[2];

    int tid;
    int status;

    // Critical section에서 하나의 스레드만 작업할 수 있도록 mutex(일종의 lock)객체를 기본 특성으로 초기화
    pthread_mutex_init(&mutex, NULL);

    // 1번 스레드를 생성하고, t1을 인자로 받은 func1의 주소부터 시작
    // 스레드 생성 실패 시 오류메시지 출력 후 종료(호출 실패시 반환되는 errno는 없다고 한다.)
    if((tid = pthread_create(&thr[0], NULL, func1, (void*)t1)) < 0){
        perror("create");
        exit(1);
    }

    // 2번 스레드를 생성하고, t2를 인자로 받은 func2의 주소부터 시작
    // 마찬가지로 호출 실패시 오류메시지 출력 후 종료
    if((tid = pthread_create(&thr[0], NULL, func2, (void*)t2)) < 0){
        perror("create");
        exit(1);
    }

    // master thread에서는 각 스레드의 종류 상태가 반화되기를 기다림
    pthread_join(thr[0], (void**)&status);
    pthread_join(thr[1], (void**)&status);

    // destroy함수를 호출해 사용했던 mutex 소멸
    pthread_mutex_destroy(&mutex);

    return 0;
}