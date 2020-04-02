#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(void){
    FILE *fp;
    int fd, n;
    char str[BUFSIZ];

    if((fp = fopen("unix.txt", "r")) == NULL){
        perror("fopen: unix.txt");
        exit(1);
    }

    fd = fileno(fp);
    printf("fd : %d\n", fd);

    n = read(fd, str, BUFSIZ);
    str[n] = '\0'; 
    printf("read str : %s\n", str);

    close(fd);
    return 0;
}