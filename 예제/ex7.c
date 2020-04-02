#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int fd;

    fd = open("unix.txt", O_CREAT | O_EXCL, 0644);
    if(fd == -1){ // system call은 실패 시 -1 리턴
        perror("Excl"); // 오류 메시지로 Excl: 오류메시지 형태로 출력
        exit(1);
    }
    close(fd);
    // open 했던 파일은 닫아주는게 인지상정
    return 0;
}

// 시스템 호출에서 파일은 저수준 상태로 작업되며
// fd라는 file descripter 변수로 작업중인 파일을 구분한다.
// 열었던 파일은 작업이 끝나면 닫아줘야된다.