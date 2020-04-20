#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
    FILE *rfp, *wfp;
    int c;

    if((rfp = fopen("unix.txt", "r")) == NULL){
        perror("fopen unix.txt");
        exit(1);
    }

    if((wfp = fopen("unix.out", "w")) == NULL){
        perror("fopen unix.out");
        exit(1);
    }

    while((c = fgetc(rfp)) != EOF){
        fputc(c, wfp);
    }

    fclose(rfp);
    fclose(wfp);

    return 0;
}

// 고수준 파일 입출력
// fopen은 open함수에 비해 조금 더 많은 기능을 제공해주는 라이브러리 함수이다.
// 파일이 존재하지 않는 경우에는 생성하며, flag도 훨씬 간결하다.
// fgetc를 통해 파일의 내용을 문자 단위로 하나씩 읽으며, while문을 통해 파일의 끝에 도달할 때 까지 읽기 작업을 수행한다.
// fputc를 통해 fgetc로 받아온 문자 하나하나를 wfp 파일 포인터가 가리키는 파일에 저장한다.