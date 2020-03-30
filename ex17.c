#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE *rfp;
    char buf[BUFSIZ];
    int n;

    if((rfp = fopen("unix.txt", "r")) == NULL){
        perror("fopen: unix.txt");
        exit(1);
    }

    while((n=fread(buf, sizeof(char), 6, rfp)) > 0){
        buf[6] = '\0';
        printf("n = %d, buf = %s\n", n, buf);
    }
    fclose(rfp);

    return 0;
}

// #include<stdio.h>
// size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);
// 버퍼 기반 입력 함수로써, 크기가 size인 데이터를 nitems에 지정한 개수만큼 읽어서 ptr에 저장한다.