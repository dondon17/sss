#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void){
    int fd;

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if((fd = open("unix.txt", O_CREAT, mode)) == -1){
        perror("creat");
        exit(1);
    }
    close(fd);

    return 0;
}

// 파일 열기 : open
// open 함수는 원래 존재하는 파일을 여는데 사용되는 함수였으며
// creat 함수는 파일을 생성하는 함수였지만
// open 함수에서 oflag값으로 O_CREAT를 설정해주면 open함수로도 파일을 생성할 수 있다.
// 또한 O_CREAT flag를 사용할 때는 반드시 mode 변수(접근권한)도 설정해주어야 한다.