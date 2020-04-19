/***************************************************************************
 *  실습과제 3 - fork 함수를 사용해 부모프로세스에서는 현재 시간을 출력하고
 *          자식 프로세스는 로그인한 사용자의 정보를 출력하는 프로그램 동기화버전
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
    printf("Parent process : Begin\n");
    if((pid = fork()) < 0){
        // fork 실패 시 오류메시지 출력 후 종료
       perror("fork");
       exit(1);
    }
    else if(pid == 0){
         // child process
        printf("Child process Begin\n");
        // child는 부모의 현재시간을 출력하는 코드가 먼저 수행되야하므로
        // 먼저 1초동안 sleep
        sleep(1);
        int a = system("who");
        printf("Child process : End\n");
        exit(1);
    }
    else if(pid > 0){
        int b;
        //Child가 종료되지 않아도 parent의 code를 계속 실행
        while(waitpid(pid, &status, WNOHANG) == 0){
            int b = system("date");
            // 현재시간을 한번만 출력하고 child가 종료해야되므로
            // 부모에서는 현제 시각 출력 후 2초등안 sleep
            sleep(3);
        }
        printf("Parent process : End\n");
    }
    return 0;
}