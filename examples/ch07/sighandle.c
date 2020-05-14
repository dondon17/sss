#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

void (*hand)(int);

void handler(int signo){
    printf("signal number : %d\n", signo);
    psignal(signo, "received signal");
}


int main(void){
    hand = signal(SIGINT, handler);
    if(hand == SIG_ERR){
        perror("signal");
        exit(1);
    }

    printf("wait SIGINT.......\n");
    pause();

    printf("wait SIGINT...............\n");
    pause();

    printf("after 2nd SIGINT...\n");

    return 0;
}