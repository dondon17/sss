#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char **argv){
    struct stat buf;

    symlink("unix.txt", "unix.sym");

    printf("1. stat : unix.txt\n");
    stat("unix.txt", &buf);
    printf("unix.txt : link count = %d\n", (int)buf.st_nlink);
    printf("unix.txt : inode = %d\n", (int)buf.st_ino);

    printf("2. stat : unix.sym\n");
    stat("unix.sym", &buf);
    printf("unix.sym : link count = %d\n", (int)buf.st_nlink);
    printf("unix.sym : inode = %d\n", (int)buf.st_ino);

    printf("3. lstat : unix.sym\n");
    lstat("unix.sym", &buf);
    printf("unix.sym : link count = %d\n", (int)buf.st_nlink);
    printf("unix.sym : inode = %d\n", (int)buf.st_ino);

    return 0;
}

// stat 함수로 symbolic link 검색 시 원본 파일의 정보를 읽어오며,
// lstat 함수로 symbolic link 검색 시 해당 심볼릭 링크의 정보를 읽어오며, 이는 원본 파일과 전혀 다른 파일이다.