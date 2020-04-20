#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    FILE *rfp, *wfp;
    char buf[BUFSIZ];
    int n;

    if((rfp = fopen("unix.txt", "r")) == NULL){
        perror("fopen unix.txt");
        exit(1);
    }

    if((wfp = fopen("unix.out", "a")) == NULL){
        perror("fopen unix.out");
        exit(1);
    }

    while((n = fread(buf, sizeof(char)*2, 3, rfp)) > 0){
        buf[6] = '\0';
        printf("n= %d\tbuf= %s\n", n, buf);
        fwrite(buf, sizeof(char)*2, n, wfp);
    }


    fclose(rfp);
    return 0;
}

// 버퍼 기반의 입출력함수 : fread, fwrite
// fread(void *buf, size_t size, size_t nitems, FILE *fp)
// 크기가 size인 데이터를 nitems만큼 파일에서 읽어와 buf에 저장하며 성공하면 읽어온 항목의 수를 리턴하게 된다.
// fwrite(void *buf, size_t size, size_t nitems, FILE *fp)
// 크기가 size인 데이터를 nitems에 지정한 개수만큼 buf에서 읽어와 파일에 저장한다.