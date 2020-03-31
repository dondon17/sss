#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    struct stat buf;
    int kind;

    stat("unix.txt", &buf);

    printf("Mode = %o(16진수 : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

    if(S_ISFIFO(buf.st_mode)) printf("unix.txt : FIFO\n");
    if(S_ISDIR(buf.st_mode)) printf("unix.txt : Directory\n");
    if(S_ISREG(buf.st_mode)) printf("unix.txt : Regular file\n"); 
    return 0;
}