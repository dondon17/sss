#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){
    FILE *fp;
    int n;
    long cur;
    char buf[BUFSIZ];

    if((fp = fopen("unix.txt", "r")) == NULL){
        perror("fopen unix.txt");
        exit(1);
    }

    cur = ftell(fp); // 현재 offset을 읽어오 저장
    printf("Offset cur = %d\n", (int)cur);

    n = fread(buf, sizeof(char), 4, fp);
    buf[n] = '\0';
    printf("Read str = %s\n", buf);

    fseek(fp, 1, SEEK_CUR);

    cur=ftell(fp);
    printf("Offset cur = %d\n", (int)cur);

    n = fread(buf, sizeof(char), 6, fp);
    buf[n] = '\0';
    printf("Read str = %s\n", buf);

    cur = 12;
    fsetpos(fp, &cur);

    fgetpos(fp, &cur);
    printf("Offset cur = %d\n", (int)cur);

    n = fread(buf, sizeof(char), 13, fp);
    buf[n] = '\0';
    printf("Read str = %s\n", buf);

    fclose(fp);
    return 0;
}

// 고수준 파일에서의 오프셋 이동 함수 : fseek
// ftell함수는 현재의 오프셋을 리턴한다.
// fsetpos를 이용해 offset을 이동시킬 수 있으며, fgetpos를 이용해 ftell과 같은 역할을 수행할 수 있다.
// fgetpos와 ftell의 차이는 ftell은 현재의 오프셋을 리턴하지만, fgetpos는 인자로 받은 변수에 현재 오프셋을 저장할 수 있다.
// cur = ftell(fp)  ->  fgetpos(fp, &cur);