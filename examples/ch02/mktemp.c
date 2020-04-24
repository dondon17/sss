#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char **argv){
    char *fname;
    char fntmp[BUFSIZ];
    char template[32];

    fname = tmpnam(NULL);
    printf("1. temp file name(tmpanm) : %s\n", fname);

    tmpnam(fntmp);
    printf("2. temp file name(tmpnam) : %s\n", fntmp);

    fname = tempnam("/tmp", "hanbit");
    printf("3. temp file name(tempnam) : %s\n", fname);

    strcpy(template, "/tmp/hanbitXXXXXX");
    fname = mktemp(template);
    printf("4. tmp file name(mktemp) : %s\n", fname);

    return 0;
}

// 다양한 방법으로 임시 파일 생성
// 1. tmpnam(char *name)
// 임시 파일명을 시스템이 알아서 생성하는 경우
// 2.tempnam(char *dir, char *name)
// 임시 파일명으로 접두어 5비트까지만 지정가능 뒤의 6비트는 시스템이 알아서 생성
// 3. mktemp(char *name)
// 임시파일의 탬플릿을 받아서 임시 파일명을 생성하며, 이때 템플릿은 대문자 X 6개로 끝나야 된다.
// exampleXXXXXX