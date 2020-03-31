#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    struct stat buf;

    stat("unix.txt", &buf);

    printf("Inode = %d\n", (int)buf.st_ino); // 해당 파일의 inode
    printf("Mode = %o\n", (unsigned int)buf.st_mode); // 파일의 형식과 접근 권한
    printf("Nlink = %o\n", (unsigned int)buf.st_nlink); // 하드링크의 개수
    printf("UID = %d\n", (int)buf.st_uid); // 파일 소유자의 uid
    printf("GID = %d\n", (int)buf.st_gid); // 파일 소유 그룹의 gid
    printf("SIZE = %d\n", (int)buf.st_size); // 파일 내용의 크기
    printf("Atime = %d\n", (int)buf.st_atime); // 마지막으로 파일을 읽거나, 실행한 시각
    printf("Mtime = %d\n", (int)buf.st_mtime); // 마지막으로 파일의 내용을 변경한 시각
    printf("Ctime = %d\n", (int)buf.st_ctime); // 마지막으로 inode의 내용을 변경한 시각
    printf("Blksize = %d\n", (int)buf.st_blksize); // 파일의 내용을 입출력할 때 사용하는 버퍼의 크기
    printf("Blocks = %d\n", (int)buf.st_blocks); // 파일을 512bytes 씩 블록으로 나눈 개수
    //printf("FStype = %s\n", buf.st_fstype);
    // 이유는 모르겠으나 stat 구조체에 st_fstpye이 정의되어 있지 않다고 한다.
    return 0;
}