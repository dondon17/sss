#include"apue.h"
#include<pthread.h>

struct foo
{
    int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp){
    printf("%s", s);
    printf("structure at 0x%lx\n", (unsigned long)fp);
    printf("foo.a = %d\n", fp->a);
    printf("foo.b = %d\n", fp->b);
    printf("foo.c = %d\n", fp->c);
    printf("foo.d = %d\n", fp->d);
}

void* func1(void *arg){
    struct foo foo = {1,2,3,4};
    printfoo("thread 1:\n", &foo);
    pthread_exit((void*)&foo);
}

void* func2(void *arg){
    printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
    pthread_exit((void*)0);
}

int main(void){
    int err;
    pthread_t t1, t2;
    struct foo *fp;

    if((err = pthread_create(&t1, NULL, func1, NULL)) != 0)
        err_exit(err, "fail to create thread 1");

    if((err= pthread_join(t1, (void*)&fp)) != 0)
        err_exit(err, "fail to join thread 1");  
    sleep(1);

    printf("parent starting second thread\n");
    if((err = pthread_create(&t2, NULL, func2, NULL)) != 0)
        err_exit(err, "fail to create thread 2");

    sleep(1);

    printfoo("parent: \n", fp);
    exit(0);
}
