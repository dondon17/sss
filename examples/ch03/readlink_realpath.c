#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
    char buf[BUFSIZ];
    int n;
    // 심볼릭 링크가 가리키는 원본 파일의 절대 경로를 출력
    realpath("unix.sym", buf);
    printf("unix.sym : realpath = %s\n", buf);

    // 심볼릭 링크의 데이터 블록에 저장된 내용을 출력
    if((n = readlink("unix.sym", buf, BUFSIZ)) == -1){
        perror("readlink");
        exit(1);
    }

    buf[n] = '\0';
    printf("unix.sym : readlink = %s\n", buf);
    return 0;
}

// realpath 함수는 말그대로 인자로 전달받은 심볼릭 링크의 원본 파일의 경로를 buf에 저장하며
// readlink 함수는 전달받은 심볼릭 링크의 데이터 블록에 저장된 내용을 buf에 저장한다.