#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    FILE *rfp, *wfp;
    char buf[BUFSIZ];

    if((rfp = fopen("unix.txt", "r")) == NULL){
        perror("fopen unix.txt");
        exit(1);
    }

    if((wfp = fopen("unix.out", "w")) == NULL){
        perror("fopen unixout");
        exit(1);
    }
    
    while(fgets(buf, BUFSIZ, rfp) != NULL)
        fputs(buf, wfp);

    fclose(rfp);
    fclose(wfp);

    return 0;
}

// fputs와 fgets는 문자열 단위로 파일을 읽어오며
// fgets에서 지정한 사이즈에서 1을 뺀 만큼 읽어온다
// BUFSIZ는 미리 정의된 상수로 256인가 그럴거다.