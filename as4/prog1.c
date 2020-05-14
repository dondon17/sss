/***************************************************************************
 *  실습과제 4 - SIGQUIT 시그널을 sigaction 함수를 사용해 붙잡고, 
 *              핸들러를 이용해 2초뒤 '아무내용'을 출력한뒤 종료하는 프로그램
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog1.c
 *  작성일: 2020 / 04 / 24
 *  마감일: 2020 / 04 / 30
 ***************************************************************************/
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

// SIGQUIT 핸들러 작성
void handler(int signo){
    psignal(signo, "Received signal ");
    printf("in signal handler, after sleep 2 secs...\n");

    sleep(2);

    printf("SSS assignment 4...\n");
    printf("after signal handler\n");
    printf("programm end\n");
    exit(1);
}

int main(int argc, char **argv){
    struct sigaction sa;
    sigset_t sgroup;

    // SIGQUIT을 제외한 다른 시그널이 입력되어도 종료되지 않도록 Block
    sigfillset(&sgroup);
    sigdelset(&sgroup, SIGQUIT);
    sigprocmask(SIG_BLOCK, &sgroup, (sigset_t *)NULL);

    // SIGQUIT 시그널에 대한 핸들러 지정  
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if(sigaction(SIGQUIT, &sa, (struct sigaction *)NULL) < 0){
        perror("sigaction");
        exit(1);
    }
    fprintf(stderr, "input SIGQUIT : ");
    pause(); // 시그널 입력 대기
    // SIGQUIT 핸들러에서 exit(1)로 인해 프로그램이 종료되고 
    // 아래 코드는 실행되지 않음을 확인
    printf("hello\n");
    return 0;
}