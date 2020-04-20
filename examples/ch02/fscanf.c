#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    FILE *rfp, *wfp;
    int id, s1, s2, s3, s4, n;
    if((rfp = fopen("unix.dat", "r")) == NULL){
        perror("fopen unix.dat");
        exit(1);
    }

    if((wfp = fopen("unix.scr", "w")) == NULL){
        perror("fopen unix.scr");
        exit(1);
    }

    fprintf(wfp, "학번      평균\n");
    while((n = fscanf(rfp, "%d %d %d %d %d", &id, &s1, &s2, &s3, &s4)) != EOF){
        fprintf(wfp, "%d : %.2lf\n", id, (s1+s2+s3+s4)/4.0);
    }

    fclose(rfp);
    fclose(wfp);

    return 0;
}

// 형식 기반 입출력 함수 : fscanf, fprintf
// fprintf(FILE *fp, ...)
// fp가 가리키는 파일에 지정된 형식으로 출력한다.
// fscanf(FILE *fp, ...)
// fp가 가리키는 파일에서 지정된 형식으로 읽어온다. 이 때 파일에 적혀있는 형식대로 변수를 사용해야한다.