/***************************************************************************
 *  실습과제 4 - 반복문과 sleep(1) 함수를 사용해 1초 간격으로 아무내용'을 출력하는 프로그램
 *              (프로그램이 ctrl + C로 종료되지 않도록 sigprocmask 함수를 이용해 블록)
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog1.c
 *  작성일: 2020 / 04 / 24
 *  마감일: 2020 / 04 / 30
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(int argc, char **argv){

    // signal set 선언 후 모든 비트 off 후 SIGINT만 on
    sigset_t group;
    sigemptyset(&group);
    sigaddset(&group, SIGINT);
    // signal set의 on 상태의 signal을 block
    sigprocmask(SIG_BLOCK, &group, (sigset_t *)NULL);

    // 1초마다 출력
    while(1){
        printf("sys programm\n");
        sleep(1);
    }

    return 0;
}