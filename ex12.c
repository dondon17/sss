#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    int fd;
    
    fd = open("tmp.bbb", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(fd == -1){
        perror("Create tmp.bbb");
        exit(1);
    }

    dup2(fd, 1);

    printf("dup2 : standard output redirection\n");
    close(fd);

    return 0;
}