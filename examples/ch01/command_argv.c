#include<stdio.h>

int main(int argc, char** argv){
    printf("argc = %d\n", argc);
    for(int i=0; i<argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);

    return 0;
}

// main 함수의 인자로 명령행에 입력된 문자열의 수와 문자열이 전달된다.
// 앞으로 명령행 인자를 쓸 필요가 없더라도 void 대신 쓰는데에 습관을 가지도록
