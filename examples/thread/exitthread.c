#include"apue.h"
#include<pthread.h>

void *func1(void *arg){
    printf("thread 1 exit with returning\n");
    return (void*) 100;
}

void *func2(void *arg){
    printf("thread 2 exit with exit code\n");
    pthread_exit((void*)200);
}

int main(int argc, char** argv){
    int err;
    pthread_t t1, t2;
    void* tret1;
    void* tret2;

    if((err = pthread_create(&t1, NULL, func1, NULL)) != 0)
        err_quit("can't create thread 1: %s\n", strerror(err));

    if((err = pthread_create(&t2, NULL, func2, NULL)) != 0)
        err_quit("can't create thread 2: %s\n", strerror(err));
    
    if((err = pthread_join(t1, &tret1)) != 0)
        err_quit("can't join thread 1: %s\n", strerror(err));
        
    if((err = pthread_join(t2, &tret2)) != 0)
        err_quit("can't join thread 2: %s\n", strerror(err));
        
    printf("thread 1 exit code : %d\n", (int)tret1);
    printf("thread 2 exit code : %d\n", (int)tret2);
}

/*   
    thread가 종료되는 3가지 경우가 있다.
    1. thread가 작업을 완료한 경우
    2. 다르 프로세스의 thread에 의해 취소된 경우
    3. thread 자신이 pthread_exit 호출한 경우

    또한 pthread_join함수는 인자로 지정된 쓰레드가 pthread_exit을 호출하거나 정상 종료될때까지 대기한다고 보면 된다.
    즉, 프로세스 생성 후, 자식 프로세스를 기다릴 때 사용하는 wait함수와 동일한 역할을 한다.
*/