#include<stdlib.h>
#include<stdio.h>

int main(void){
    FILE *rfp;
    int id, s1, s2, s3, s4, n;

    if((rfp = fopen("unix.dat", "r")) == NULL){
        perror("fopen: unix.dat");
        exit(1);
    }

    printf("학번 평균\n");
    // 주의 할 점은 파일에 기록되어 있는 자료형대로 지정해줘야 한다.
    while((n = fscanf(rfp, "%d %d %d %d %d", &id, &s1, &s2, &s3, &s4)) != EOF) printf("%d : %d\n", id, (s1+s2+s3+s4)/4);

    fclose(rfp);

    return 0;
}