#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(void){
    struct stat buf;

    stat("unix.txt", &buf);
    printf("before link count = %d\n", (int)buf.st_nlink);

    link("unix.txt", "unix.ln");

    stat("unix.txt", &buf);
    printf("after link count = %d\n", (int)buf.st_nlink);
    
    return 0;
}