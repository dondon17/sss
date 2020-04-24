#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    int fd, n;
    char buf[BUFSIZ];
    off_t start, cur;
    if((fd = open("unix.txt", O_RDONLY)) == -1){
        perror("open unix.txt");
        exit(1);
    }

    start = lseek(fd, 0, SEEK_CUR);
    n = read(fd, buf, BUFSIZ);
    buf[n] = '\0';

    printf("Offset start= %d\nRead str= %sn= %d\n", (int)start, buf, n);
    cur = lseek(fd, 0, SEEK_CUR);
    printf("Offset cur= %d\n", (int)cur);

    start = lseek(fd, 5, SEEK_SET);
    n = read(fd, buf, BUFSIZ);
    buf[n] = '\0';

    printf("Offset start= %d\nRead str= %sn= %d\n", (int)start, buf, n);

    close(fd);

    return 0;
}

// 파일의 오프셋을 지정, 검색하는 함수 : lseek(int fd, off_t offset, int whence)
// fd에 저장된 파일에서 whence를 기준으로 offset만큼의 위치로 이동
// SEEK_CUR로 설정하고 오프셋을 0으로 설정하면, 현재 위치로 이동하게 된다.
// SEEK_END로 설정하고 0으로 설정하는 경우 파일의 끝으로 이동하게 됨.