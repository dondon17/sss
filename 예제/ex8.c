#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void){
    int fd;
    close(0);
    // 표준 입력에 해당되는 0번 fd를 닫음으로써 0번이 비어있게됨.

    fd = open("unix.txt", O_RDWR);
    // fd에는 3번이 아닌 0번이 할당됨
    if(fd == -1){
        perror("Excl");
        exit(1);
    }

    printf("unix.txt : fd = %d\n", fd);
    close(fd);
    return 0;
}