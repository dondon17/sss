#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(void){
    FILE *fp;
    int fd;
    char str[BUFSIZ];

    fd = open("unix.txt", O_RDONLY);
    if(fd == -1){
        perror("open: unix.txt");
        exit(1);
    }

    // 저수준으로 열었던 파일을 고수준으로 전환
    fp = fdopen(fd, "r");

    fgets(str, BUFSIZ, fp);
    printf("read: %s\n", str);

    fclose(fp);
    return 0;
}