#include<stdio.h>

int main(int argc, char* argv[]){
    int n;
    printf("argc = %d\n", argc);
    for(n=0; n<argc; n++) printf("argv[%d] = %s\n", n, argv[n]);

    return 0;
}

// 명령행 인자 출력하기
// 명령행 인자의 전달은 main 함수로 자동으로 전달된다.