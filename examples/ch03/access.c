#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/errno.h>

extern int errno;

int main(int argc, char **argv){
    int per;

    if(access("unix.bak", F_OK) == -1) perror("unix.bak");
    
    if(access("unix.txt", R_OK) == -1 && errno == EACCES) printf("unix.txt : Read permission is not permitted\n");
    else printf("unix.txt : Read permission is permitted\n");

    return 0;
}

// access 함수를 이용해 파일의 접근 권한을 검색할 수 있다.
// access(파일명, 옵션)
// 옵션에는 파일의 존재여부의 F_OK, 읽기모드 가능 여부의 R_OK, 쓰기모드 가능 여부의 W_OK, 실행모드 가능 여부의 X_OK가 있다.
// 해당 옵션에 대해 -1를 리턴하면 권한이 없거나 파일이 없음을 의미하고
// 0을 리턴할 경우 파일이 존재하고 해당 권한도 가지고 있음을 의미한다.