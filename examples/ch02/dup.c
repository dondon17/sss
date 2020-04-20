#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    int fd, fd2;

    if((fd = open("tmp.aaa", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1){
        perror("open tmp.aaa");
        exit(1);
    }
    close(1);
    fd2 = dup(fd);

    printf("dup fd = %d\n", fd2);
    printf("Standard output redirection\n");
    close(fd);

    return 0;
}

// 표준 출력인 1번 fd를 닫음으로써 1번 fd가 비어있게 됨
// fd2에 fd를 복사함으로써 fd2는 표준 출력에 할당되고, fd로 열었던 파일은 표준 출력이 됨.
// dup 이후 printf로 출력하는 모든 것들이 터미널, 즉 모니터가 아닌 tmp.aaa 파일로 저장됨.
// standard output redirection