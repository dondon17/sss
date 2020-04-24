#include<stdio.h>
#include<unistd.h>
#include<sys/errno.h>
#include<stdlib.h>

extern int errno;

int main(void){
    FILE *fp;

    if((fp = fopen("unix.txt", "r")) == NULL){
        printf("errno = %d\n", errno);
        exit(1);
    }

    close(fp);
    return 0;
}

// 라이브러리 함수의 오류처리 방법
// 라이브러리 함수 호출 실패시에는 NULL이 반환된다
// errno 변수에는 발생한 에러의 오류코드 저장