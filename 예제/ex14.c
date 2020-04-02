#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    int cnt;

    // 현재 tmp.aaa 파일의 링크수가 1이므로 unlink시 아예 삭제된다.
    cnt = unlink("tmp.aaa");

    if(cnt == -1){
        perror("unlinik tmp.aaa");
        exit(1);
    }

    printf("Unlink tmp.aaa success!!\n");
    return 0;
}

// 실행파일 실행 후 ls 명령어로 확인하면 tmp.aaa 파일이 제거된 것을 알 수 있다.