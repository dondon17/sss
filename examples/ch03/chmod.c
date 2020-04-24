#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>

int main(void){
    struct stat buf;

    chmod("unix.txt", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH);
    stat("unix.txt", &buf);
    printf("1. Mode = %o\n", (unsigned int)buf.st_mode);

    buf.st_mode |= S_IWGRP;
    chmod("unix.txt", buf.st_mode);
    stat("unix.txt", &buf);
    printf("2. Mode = %o\n", (unsigned int)buf.st_mode);
    
    buf.st_mode &= ~(S_IROTH);
    chmod("unix.txt", buf.st_mode);
    stat("unix.txt", &buf);
    printf("3. Mode = %o\n", (unsigned int)buf.st_mode);

    return 0;

}

// 파일의 mode 접근 권한을 바꾸는 함수 : chmod
// 먼저 stat이나 fstat를 통해 파일의 정보를 검색한 다음
// stat 구조체의 st_mode 값에 원하는 접근권한 관련 상수를 추가하거나 제거할 수 있다.