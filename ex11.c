#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd, fd1;

    fd = open("tmp.aaa", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if(fd == -1){
        perror("create tmp.aaa");
        exit(1);
    }
    close(1); // 표준 출력을 닫음으로써 1번 fd가 비어있게 됨.

    fd1 = dup(fd); // fd를 복사하면 비어있는 수 중 가작 작은 1(표준 출력)에 복사

    // 아래 printf 두 줄이 터미널이 아닌 tmp.aaa에 출력됨
    printf("Dup fd = %d\n", fd1);
    printf("Standard output redirection\n");
    close(fd);

    return 0;
}