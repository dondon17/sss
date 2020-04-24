#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>

int main(void){
    DIR *dp;
    struct dirent *dent;

    if((dp = opendir("hanbit")) == NULL){
        perror("opendir:hanbit");
        exit(1);
    }

    // 열린 디렉토리 내의 디렉토리 항목을 읽어와 dent 포인터 변수에 저장
    while((dent = readdir(dp)))
        printf("name : %s\tInode : %d\n", dent->d_name, (int)dent->d_ino);
    
    closedir(dp);
    return 0;
}