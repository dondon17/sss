#include<sys/errno.h>
#include<unistd.h>
#include<stdio.h>

extern int errno;

int main(void){
    int per;

    // 현재 디렉토리에 unix.bak 파일이 없으므로 access함수는 -1을 리턴
    // ENOENT는 파일이 없음을 의미하는 오류메시지
    if(access("unix.bak", F_OK) == -1 && errno == ENOENT)
        printf("unix.bak: file not exist.\n");

    per = access("unix.txt", R_OK);
    if(per == 0)
        printf("unix.txt: read permission is permitted.\n");
    
    // EACCES는 파일 접근 권한이 없음을 의미하는 오류메시지
    else if(per == -1 && errno == EACCES)
        printf("unix.txt: read permission is not permitted.\n");

    // access 함수는 시스템 호출 함수이기 때문에 성공시 0 실패시 -1을 리턴한다
    return 0;
}