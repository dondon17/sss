#include<stdio.h>
#include<unistd.h>
#include<sys/errno.h>

extern int errno;

int main(void){
    if(access("unix.txt", F_OK) == -1)
        printf("errno = %d\n", errno);

    return 0;
}

// 시스템 호출의 오류 처리방법
// 호출 성공시 알맞은 return값이 반환되고
// 호출 실패시 -1 리턴
// errno변수에는 해당 에러의 오류코드가 저장된다.