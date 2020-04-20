#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char **argv){
    struct stat buf;

    stat("unix.txt", &buf);

    printf("Mode = %o (in hex: %x)\n", (unsigned int)buf.st_mode, (unsigned int)buf.st_mode);
    
    int kind = buf.st_mode & __S_IFMT;
    printf("kind = %o (in hex: %x)\n", kind, kind);

    switch (kind){
        case __S_IFIFO:
            printf("unix.txt : FIFO\n");    
            break;
        case __S_IFDIR:
            printf("unix.txt : directory\n");
            break;
        case __S_IFREG:
            printf("unix.txt : regular file\n");
            break;
    }

    return 0;
}

// st_mode 에는 파일의 종류와 접근권한이 담겨있는데
// st_mode 값에 S_IFMT를 AND연산시키면, 파일의 종류만 남아있게 된다.
// S_IFMT는 파일의 종류를 정의한 부분만 가져온다. (st_mode의 맨 앞 1비트 값)

// 파일명으로 파일의 정보를 검색하는 함수 stat(char *filename, struct stat *buf)
// 매개변수로 입력받은 파일에 대한 정보를 stat구조체 변수에 저장
// 파일의 정보에는 inode 번호, 파일의 종류, uid, gid, 링크 수, 접근권한 등 다양한 정보가 존재한다.