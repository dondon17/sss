#include<stdio.h>
#include<unistd.h>
#include<sys/errno.h>
#include<stdlib.h>
#include<string.h>

extern int errno;

int main(void){
    char *err;

    if(access("unix.txt", F_OK) == -1){
        err = strerror(errno);
        printf("ERROR: %s(unix.txt)\n", err);
        exit(1);
    }

    return 0;
}

// strerror(int errno): 오류 코드에 해당하는 오류 메시지를 리턴
// 발생한 오류에 대한 오류 코드를 파라미터로 받아 해당 코드의 오류 메시지 리턴
// string.h 헤더가 필요하다
// perror는 알아서 오류 메시지를 출력해준다면 
// strerror는 발생한 오류 중 원하는 오류 코드에 대한 메시지를 출력해준다는 장점이 있음.