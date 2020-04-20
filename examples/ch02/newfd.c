#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd;

    close(0);

    if((fd = open("unix.txt", O_RDWR)) == -1){
        perror("open");
        exit(1);
    }
    printf("unix.txt : %d\n", fd);
    close(fd);

    return 0;
}

// fd에는 비어있는 작은 숫자부터 파일이 할당되는데
// 0번: 표준입력, 1번: 표준출력, 2번: 표준오류로 기본적으로 할당되어있다.
// close(0) 수행시 표준 입력(키보드)이 닫히고, 0번 fd는 비어있게 되고 새로 열린 파일은 0번 fd를 할당받게 된다.