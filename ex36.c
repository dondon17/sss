#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    char *cwd;
    char wd[BUFSIZ];

    // 현재 작업 디렉토리를 getcwd 함수를 통해 가져옴
    cwd = getcwd(NULL, BUFSIZ);
    printf("1. current directory : %s\n", cwd);
    
    // 현재 작업 디렉토리 변경
    chdir("kkkkk");

    // getcwd의 매개변수로 작업 디렉토리 주소를 저장할 문자열 배열을 전달
    getcwd(wd, BUFSIZ);
    printf("2. current directory : %s\n", wd);
    return 0;
}