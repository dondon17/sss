#include<stdio.h>
#include<stdlib.h>
//#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(void){
    FILE *fp;
    int id, s1, s2, s3, n;

    if((fp = fopen("data", "r")) == NULL){
        perror("fopen: data");
        exit(1);
    }
    
    printf("   학번   평균   \n");
    while((n = fscanf(fp, "%d %d %d %d", &id, &s1, &s2, &s3)) != EOF)
        printf("%d : %.2lf\n", id, (s1+s2+s3)/3.0);
    
    fclose(fp);
    return 0;
}