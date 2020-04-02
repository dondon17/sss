#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(void){
    if(mkdir("direc", 0755) == -1){
        perror("direc");
        exit(1);
    }
    if(mkdir("tory", 0755) == -1){
        perror("tory");
        exit(1);
    }

    if(rename("direc", "kkkkk") == -1){
        perror("kkkkk");
        exit(1);
    }

    if(rmdir("tory") == -1){
        perror("tory");
        exit(1);
    }

    return 0;
}