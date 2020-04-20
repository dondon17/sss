#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    int fd;
    
    if((fd = open("tmp.bbb", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1){
        perror("open tmp.bbb");
        exit(1);
    }

    dup2(fd, 1);

    printf("tmp.bbb = %d\n", fd);
    printf("dup2 : standard output redirection\n");
    close(fd);
}

// dup2는 dup보다 조금더 간단한 방법으로 파일 지시자를 복사한다.
// * 참고로 dup는 시스템 호출이고 dup2는 라이브러리 함수이다.
// fd는 그대로 3이지만, 표준 출력에 복사되었으므로, tmp.bbb로 표준출력이 redirection되었다.