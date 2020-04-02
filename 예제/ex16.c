#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE *rfp, *wfp;
    char buf[BUFSIZ];

    if((rfp = fopen("unix.txt", "r")) == NULL){
        perror("fopen: unix.txt");
        exit(1);
    }

    if((wfp = fopen("unix.out", "w")) == NULL){
        perror("fopen: unix.out");
        exit(1);
    }

    // 한 행씩 buf로 읽어서 파일로 출력
    // 문자열 기반 입출력 함수 fgets, fputs
    while(fgets(buf, BUFSIZ, rfp) != NULL) fputs(buf, wfp);

    fclose(rfp);
    fclose(wfp);
    return 0;
}