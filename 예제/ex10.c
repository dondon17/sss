#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void){
    int fd, n;
    off_t start, cur;
    char buf[256];

    fd = open("unix.txt", O_RDONLY);
    if(fd == -1){
        perror("open unix.txt");
        exit(1);
    }

    // start 변수에 파일의 현재 위치 기준 첫번 째 위치를 저장
    start = lseek(fd, 0, SEEK_CUR);
    // 변수 n에 읽어온 내용의 마지막 인덱스 저장
    n = read(fd, buf, 13);
    buf[n] = '\0';
    // 마지막 인덱스를 null로 초기화

    printf("offset start = %d\nread str = %s\nn=%d\n", (int)start, buf, n);
    cur = lseek(fd, 0, SEEK_CUR);
    // 현재 위치 기준 위치를 cur에 저장
    printf("offset cur = %d\n", (int)cur);
    return 0;
}