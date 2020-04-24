#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

int main(void){
    int fd;

    if((fd = open("unix.txt", O_CREAT | O_EXCL)) == -1){
        perror("unix.txt");
        exit(1);
    }
    close(fd);

    return 0;
}

// O_EXCL flag는 O_CREAT flag와 함께 많이 사용된다.
// 이미 있는 파일의 경우 생성하지 않고 오류 메시지를 출력한다.