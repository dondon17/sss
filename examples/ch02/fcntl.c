#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    int fd, flags;

    if((fd = open("unix.txt", O_RDWR)) == -1){
        perror("open unix.txt");
        exit(1);
    }

    if((flags = fcntl(fd, F_GETFL)) == -1){
        perror("fcntl get flags");
        exit(1);
    }

    flags |= O_APPEND;

    if((flags = fcntl(fd, F_SETFL, flags)) == -1){
        perror("fcntl set flag");
        exit(1);
    }

    if(write(fd, "hanbif media", 12) != 12) perror("write");
    close(fd);

    return 0;
}

// 파일 기술자가 가리키는 파일에 fcntl함수의 인자로 전달받은 명령을 수행한다
// 자주 사용되는 명령으로는 파일의 상태 flag정보를 알아오는 F_GETFL와, 상태 flag 정보를 설정하는 F_SETFL가 있다.