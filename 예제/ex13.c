#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>

int main(void){
    int fd, flags;

    fd = open("unix.txt", O_RDWR);
    if(fd == -1){
        perror("open");
        exit(1);
    }

    // fcntl(fd, F_GETFD)를 통해 현재 fd에 해당하는 파일이 어떤 flag로 열렸는지의 상태 정보를 가져옴
    if((flags = fcntl(fd, F_GETFD)) == -1){
        perror("fcntl");
        exit(1);
    }

    // 처음 flag O_RDWR에다가 O_APPEND 플래그 추가
    flags |= O_APPEND;

    // 새로 추가된 플래그로 다시 설정
    if(fcntl(fd, F_SETFL, flags) == -1){
        perror("fcntl");
        exit(1);
    }

    // unix.txt파일에 있던 내용에 이어서 write됨
    if(write(fd, "dondon hello\n", 12) != 12) perror("write");

    close(fd);
    return 0;
}