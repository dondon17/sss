#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    FILE *fp;
    int fd, n;
    char buf[BUFSIZ];

    if((fp = fopen("unix.txt", "r")) == NULL){
        perror("fopen unix.txt");
        exit(1);
    }

    fd = fileno(fp);
    printf("fd= %d\n", fd);

    n = read(fd, buf, BUFSIZ);
    printf("Read str= %s\n", buf);

    close(fd);

    return 0;
}

// 고수준 파일입출력의 파일포인터를 저수준 파일입출력의 파일 기술자로 변환: fileno(fp)
// 고수준으로 열린 파일을 저수준의 파일 기술자에 할당하고, 저수준에서의 파일 입출력 작업이 가능