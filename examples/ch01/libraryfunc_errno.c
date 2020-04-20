#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>

extern int errno;

int main(void){
    FILE *fp;

    if((fp = fopen("unix.txt", "r")) == NULL){
        printf("errno = %d\n", errno);
        exit(1);
    }
    return 0;
}