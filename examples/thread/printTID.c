#include"apue.h"
#include<pthread.h>

void printtid(const char *s){
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s, pid: %u, tid: %u(0x%x)\n", 
            s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void *func(void *arg){
    printtid("new thread: ");
    return (void*)0;
}

int main(int argc, char **argv){
    int err;
    pthread_t ntid;
    err= pthread_create(&ntid, NULL, func, NULL);
    if(err != 0){
        err_quit("Creating thread failed..\n", strerror(err));
    }

    printtid("main thread: ");
    sleep(1);
    return 0;
}

/*
    thread를 생성해 생성된 thread의 pid와 tid를 확인하는 예제.

    thread의 생성은 pthread_create함수를 통해 이루어지며,
    시작할 함수의 주소, 함수에 전달할 매개변수, 쓰레드 속성 등을 설정하며 pthread_t 변수에 쓰레드 id를 저장한다.

    기본적으로 쓰레드는 생성하지 않은 경우, 프로세스는 master thread 즉, 싱글 쓰레드로 동작한다.
*/