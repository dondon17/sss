#include<stdlib.h>
#include<stdio.h>
int main(void){
    FILE *fp;
    int n;
    long cur;
    char buf[BUFSIZ];

    if((fp = fopen("unix.txt", "r")) == NULL){
        perror("fopen: unix.txt");
        exit(1);
    }
    // 현재 offset을 읽어 옴 cur = 0 
    cur = ftell(fp);
    printf("Current Offset = %d\n", (int)cur);

    // fread로 fp에서 sizeof(char) * 4 만큼 읽어옴
    n = fread(buf, sizeof(char), 4, fp);
    buf[n] = '\0';
    printf("-- read str = %s\n", buf);

    // 1만큼 offset 이동
    fseek(fp, 1, SEEK_CUR);

    // fseek 함수에 의해 cur이 4에서 5로 증가
    cur = ftell(fp);
    printf("Current Offset = %d\n", (int)cur);

    n = fread(buf, sizeof(char), 6, fp);
    buf[n] = '\0';
    printf("-- read str = %s\n", buf);

    // offset을 지정하여 이동 
    cur = 12;
    fsetpos(fp, &cur);

    // 현재 offset을 읽어서 지정
    fgetpos(fp, &cur);
    printf("Current Offset = %d\n", (int)cur);    

    n = fread(buf, sizeof(char), 13, fp);
    buf[n] = '\0';
    printf("-- read str = %s\n", buf);

    fclose(fp);
    return 0;
}