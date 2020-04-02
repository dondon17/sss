#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<dirent.h>

int main(void){
    DIR *dp;
    struct dirent *dent;

    // directory 열기 : opendir(디렉토리명)
    if((dp = opendir("kkkkk")) == NULL){
        perror("opendir : kkkkk");
        exit(1);
    }

    // directory 정보 읽기 : readdir(디렉토리 포인터)
    while((dent = readdir(dp))){
        printf("name :%s   ", dent->d_name);
        printf("Inode : %d   \n", (int)dent->d_ino);
    }

    // directory 닫기 : closedir(디렉토리 포인터)
    closedir(dp);
    return 0;
}