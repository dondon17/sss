#include"apue.h"
#include<pthread.h>

void cleanup(void *arg){
    printf("cleanup: %s\n", (char*)arg);
}

void* func1(void* arg){
    printf("thread 1 start\n");
    pthread_cleanup_push(cleanup, "thread 1 first handler");
    pthread_cleanup_push(cleanup, "thread 1 second handler");
    printf("thread 1 push complete\n");
    if(arg) return (void*)1;
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);

    return (void*)1;           
}

void* func2(void* arg){
    printf("thread 2 start\n");
    pthread_cleanup_push(cleanup, "thread 2 first handler");
    pthread_cleanup_push(cleanup, "thread 2 second handler");
    printf("thread 2 push complete\n");
    if(arg) return (void*)2;

    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);

    return (void*)2;           
}

int main(int argc, char** argv){
    int err;
    pthread_t t1, t2;
    void *tret;

    if((err=pthread_create(&t1, NULL, func1, NULL)) != 0)
        err_quit("failed to create thread 1: %s\n", strerror(err));
    if((err=pthread_create(&t2, NULL, func2, NULL)) != 0)
        err_quit("failed to create thread 2: %s\n", strerror(err));

    if((err=pthread_join(t1, &tret)) != 0)
        err_quit("failed to join thread 1: %s\n", strerror(err));    
    printf("thread 1 exit code : %d\n", (int)tret);

    if((err=pthread_join(t2, &tret)) != 0)
        err_quit("failed to join thread 2: %s\n", strerror(err));    
    printf("thread 2 exit code : %d\n", (int)tret);

    exit(0);
}