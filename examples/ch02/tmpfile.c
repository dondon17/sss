#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    FILE *fp;

    fp = tmpfile();

    fputs("unix system", fp);

    fclose(fp);
    return 0;
}

// 자동으로 w+모드로 열린 파일 포인터를 리턴하는 함수 : tmpfile()
// 현재 w+모드로 열린 파일이 없으므로 fp가 가리키는 파일은 없다.
// tmpfile은 쓰기전용으로 열린 파일을 다시한번 참조할 때 편리하게 사용할 수 있다.