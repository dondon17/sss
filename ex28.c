#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    struct stat buf;
    int kind;

    stat("unix.txt", &buf);

    printf("Mode = %o(16진수 : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

    if((buf.st_mode & __S_IREAD) != 0)
        printf("unix.txt : user has a read permission\n");

    if((buf.st_mode & (__S_IREAD >> 3)) != 0)
        printf("unix.txt : group has a read permission\n");

    if((buf.st_mode & S_IROTH) != 0)
        printf("unix.txt : other has a read permission\n");

    return 0;
}