#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
int main(int argc, char **argv){
    struct stat buf;
    int fd;

    if((fd = open("unix.txt", O_RDWR)) == -1){
        perror("open unix.txt");
        exit(1);
    }

    fstat(fd, &buf);

    printf("I node = %ld\n", buf.st_ino);
    printf("Mode = %o\n", (unsigned int)buf.st_mode);
    printf("Nlink = %o\n", (unsigned int)buf.st_nlink);
    printf("UID = %d\n", (int)buf.st_uid);
    printf("GID = %d\n", (int)buf.st_gid);
    printf("Size = %d\n", (int)buf.st_size);
    printf("Atime = %d\n", (int)buf.st_atime);
    printf("Mtime = %d\n", (int)buf.st_mtime);
    printf("Ctime = %d\n", (int)buf.st_ctime);
    printf("Blksize = %d\n", (int)buf.st_blksize);
    printf("Blocks = %d\n", (int)buf.st_blocks);
    // printf("FStype = %s\n", buf.st_fstype);

    return 0;
}

// 파일명 기술자로 파일의 정보를 검색하는 함수 fstat(int fd, struct stat *buf)
// 매개변수로 입력받은 파일 기술자가 가리키는 파일에 대한 정보를 stat구조체 변수에 저장
// 파일의 정보에는 inode 번호, 파일의 종류, uid, gid, 링크 수, 접근권한 등 다양한 정보가 존재한다.