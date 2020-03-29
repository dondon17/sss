#include<stdlib.h>
#include<stdio.h>
#include<sys/errno.h>
#include<string.h>
#include<unistd.h>

extern int errno;

int main(void){
    char *err;

    if(access("unix.txt", R_OK) == -1){
        err = strerror(errno);
        printf("오류: %s(unix.txt)\n", err);
        exit(1);
    }
    return 0;
}

// strerror 함수를 이용해 error 메시지 출력
// 매개변수로 해당 오류의 errno가 들어간다.
// 전달받은 errno의 메시지를 출력

// #include<string.h>
// char *strerror(int errno)