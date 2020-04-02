#include<sys/errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    if(access("unix.txt", R_OK) == -1){
        perror("unix.txt");
        exit(1);
    }
    return 0;
}

// perror 라이브러리 함수로 오류 메시지 출력
// 매개변수로 오류 메시지 앞에 올 내용을 받는다.
// 발생한 오류에 대한 에러 메시지 출력

// #include<stdio.h>
// void perror(const char *s);
