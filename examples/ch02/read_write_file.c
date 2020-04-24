#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    int rfd, wfd;
    int n;
    char buf[BUFSIZ];

    if((rfd = open("unix.txt", O_RDONLY)) == -1){
        perror("open unix.txt");
        exit(1);
    }

    if((wfd = open("unix.bak", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1){
        perror("open unix.bak");
        exit(1);
    }

    while((n = read(rfd, buf, 6)) > 0){
        if(write(wfd, buf, n) != n) perror("read");
    }

    close(rfd);
    close(wfd);

    return 0;
}

// 읽어올 파일과, 쓸 파일을 각각 열어서 읽을 파일의 내용을 쓰기 파일에 저장
// read(int fd, void *buf, int bytes)
// fd에 저장된 파일에서 bytes만큼 읽어와 buf에 저장하며 읽어온 바이트 수를 리턴하고, 0을 리턴하는 경우 EOF도달
// write(int fd, void *buf, int bytes)
// fd에 저장된 파일에 buf의 내용을 bytes씩 쓰기를 수행하며 쓴 바이트 수를 리턴한다.
// while문을 통해 파일의 내용을 복사하는 것은 자주 사용되니 알아두도록 하자.