#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    struct stat buf;
    int kind;

    stat("unix.txt", &buf);

    printf("Mode = %o(16진수 : %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);

    kind = buf.st_mode & __S_IFMT;

    printf("kind = %x\n", kind);
    
    switch (kind){
        case __S_IFIFO:
            printf("unix.txt : FIFO\n");
            break;
        case __S_IFDIR:
            printf("unix.txt : Directory\n");
            break;
        case __S_IFREG:
            printf("unix.txt : Regular file\n");
            break;
    }
    return 0;
}