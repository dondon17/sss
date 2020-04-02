#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
int main(void){
    char buf[BUFSIZ];
    char buf2[BUFSIZ];

    int n;
    // 심볼릭 링크에 데이터 블록에 저장된 내용을 읽어옴 - readlink 함수
    if((n = readlink("unix.sym", buf, BUFSIZ)) == -1){
        perror("readlink");
        exit(1);
    }

    buf[n] = '\0';
    printf("unix.sym : readlink = %s\n", buf);

    // 심볼릭 링크의 원볼 파일의 실제 경로명을 읽어옴 - realpath 함수
    realpath("unix.sym", buf2);
    printf("unix.sym : realpath = %s\n", buf2);
    return 0;
}