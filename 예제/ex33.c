#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    struct stat buf;

    printf("1. stat : unix.txt --- \n");
    stat("unix.txt", &buf);
    printf("unix.txt : link count = %d\n", (int)buf.st_nlink);
    printf("unix.txt : Inode = %d\n", (int)buf.st_ino);

    // stat으로 symbolic 링크를 검색하면 원본 파일에 대한 정보를 불러온다.
    printf("2. stst : unix.sym --- \n");
    stat("unix.sym", &buf);
    printf("unix.sym : link count = %d\n", (int)buf.st_nlink);
    printf("unix.sym : Inode = %d\n", (int)buf.st_ino);


    // lstat으로 symbolic 링크를 검색하면 symbolic 링크 자체에 대한 정보를 불러온다.
    printf("3. lstat : unix.sym --- \n");
    lstat("unix.sym", &buf);
    printf("unix.txt : link count = %d\n", (int)buf.st_nlink);
    printf("unix.txt : Inode = %d\n", (int)buf.st_ino);

    return 0;
}