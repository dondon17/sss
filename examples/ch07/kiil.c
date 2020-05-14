#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
    printf("Before SIGCONT signal to parent....\n");

    kill(getppid(), SIGCONT);

    printf("Before SIGQUIT signal to me....\n");

    kill(getpid(), SIGQUIT);

    printf("After SIGQUIT to me...\n");

    return 0;
}