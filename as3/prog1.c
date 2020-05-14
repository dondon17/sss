/***************************************************************************
 *  실습과제 3 - fork 함수를 사용해 부모프로세스에서는 현재 시간을 출력하고
 *           자식 프로세스는 로그인한 사용자의 정보를 출력하는 프로그램 동기화 x
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog2.c
 *  작성일: 2020 / 04 / 18
 *  마감일: 2020 / 04 / 22
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(void){
    pid_t pid;
    int status;
    // parent process    
    printf("Parent process : Begin\n");
    if((pid = fork()) < 0){
        // fork 실패한 경우 에러 메시지 출력 후 종료
       perror("fork");
       exit(1);
    }
    else if(pid > 0){
        // 부모는 자식의 종료상태를 기다리지 않고 현재 시각 출력 후 종료
        int b = system("date");
        printf("Parent process : End\n");
    }
    else if(pid == 0){
        // child process
        printf("Child process Begin\n");
        // 좀비로 되기 위해 부모가 실행되도록 2초동안 sleep
        sleep(2);
        // 꺠어나서 사용자 로그인 시간 출력 후 종료
        int a = system("who");
        printf("Child process : End\n");
        exit(1);
    }
    return 0;
}