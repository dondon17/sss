#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include</usr/include/errno.h>

extern int errno;

/*
// 1번 코드
int main(void){
    if (access("unix,txt", F_OK) == -1) printf("errno=%d\n", errno);
    return 0;
}
*/

// 2번 코드
int main(void){
    FILE *fp;

    if((fp=fopen("unix.txt", "r")) == NULL){
        printf("errno=%d\n", errno);
        exit(1);
    }
    fclose(fp);
    return 0;
}

// 1번 코드는 시스템 호출의 오류 처리방법을 보여주는 코드
// 시스템 호출은 성공하면 0을, 실패하면 -1을 리턴한다.

// 2번 코드는 라이브러리 함수의 오류 처리방법을 보여주는 코드
// 라이브러리 함수는 오류발생 시 NULL을 리턴하고, 함수의 리턴값이 int형이면 -1을 리턴한다.
