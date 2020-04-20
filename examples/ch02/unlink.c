#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    int cnt;

    cnt = unlink("tmp.aaa");
    if(cnt == -1){
        perror("unlink tmp.aaa");
        exit(1);
    }

    printf("unlink tmp.aaa success!\n");

    return 0;
}

// unlink는 파라미터로 전달받은 파일의 link수를 감소시키는 함수이며
// link개수가 0이 되면 파일은 삭제된다.
// unlink를 하더라도 link count가 0이 아니라면 파일은 삭제되지 않고 링크수만 줄어든다.