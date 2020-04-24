#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char **argv){
    struct stat buf;

    stat("unix.txt", &buf);
    printf("before link file = %d\n", (int)buf.st_nlink);

    link("unix.txt", "unix.ln");

    stat("unix.txt", &buf);
    printf("after link file = %d\n", (int)buf.st_nlink);

    return 0;
}

// unix.txt 파일에 하드링크를 생성
// 하드 링크는 원본파일과 동일한 inode를 갖는다!