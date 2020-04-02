#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(void){
    int rfd, wfd, n;
    char buf[10];

    // 내용을 읽어올 파일을 읽기 전용으로 open
    rfd = open("unix.txt", O_RDONLY);
    if(rfd == -1){
        perror("open unix.txt");
        exit(1);
    }

    // 내용을 쓸 파일은 없는 경우 만들고, 내용이 있으면 다 지우고 새로 쓰고, 쓰기전용으로 open
    wfd = open("unix.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(wfd == -1){
        perror("open unix.bak");
        exit(1);
    }

    // 6byte씩 rfd에서 읽어와 buf에 저장하고
    // 다 읽어올 때까지 wfd에 씀
    while((n=read(rfd, buf, 6)) > 0){
        if(write(wfd, buf, n) != n) perror("write");
    }  
    if(n == -1) perror("read");

    close(rfd);
    close(wfd);

    return 0;
}