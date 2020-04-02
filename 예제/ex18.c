#include<stdio.h>
#include<stdlib.h>

int main(void){
    FILE *rfp, *wfp;
    char buf[BUFSIZ];
    int n;

    if((rfp = fopen("unix.txt", "r")) == NULL){
        perror("fopen: unix.txt");
        exit(1);
    }

    if((wfp = fopen("unix.out", "w")) == NULL){
        perror("fopen: unix.out");
        exit(1);
    }

    // rfp 에서 항목크기가 sizeof(char), 이것을 6개 즉 6바이트씩 읽어서 출력
    while((n = fread(buf, sizeof(char), 6, rfp)) > 0) fwrite(buf, sizeof(char), n , wfp);

    fclose(rfp);
    fclose(wfp);

    return 0;
}