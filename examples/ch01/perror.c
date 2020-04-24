#include<stdio.h>
#include<stdlib.h>
#include<sys/errno.h>
#include<unistd.h>

int main(void){
    if(access("unix.txt", F_OK) == -1){
        perror("unix.txt");
        exit(1);
    }
    return 0;
}

// perror(char*): 오류 메시지 출력 함수
// 발생한 오류에 대해 해당 오류 메시지 출력
// stdio.h 헤더가 필요하다