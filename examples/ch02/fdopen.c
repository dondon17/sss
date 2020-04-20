#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE *fp;
    int fd;
    char buf[BUFSIZ];

    if((fd = open("unix.txt", O_RDWR)) == -1){
        perror("open unix.txt");
        exit(1);
    }

    fp = fdopen(fd, "r");
    fgets(buf, BUFSIZ, fp);
    printf("Read str= %s\n", buf);

    fclose(fp);
    
    return 0;
}

// 저수준으로 open한 파일을 고수준으로 파일 입출력의 포인터로 변환 : fdopen(fd, mode)
// 저수준 파일의 파일 기술자를 매개변수로 전달해 고수준 파일입출력의 파일 포인터 변수로 변환시키는 함수