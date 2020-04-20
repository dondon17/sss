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