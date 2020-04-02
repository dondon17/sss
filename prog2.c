#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(void){
    int fd, n;
    int i = 0, sum = 0;
    char buf[BUFSIZ];
    char *arr[10]={NULL, };

    if((fd = open("data", O_RDONLY)) == -1){
        perror("open: data");
        exit(1);
    }

    n = read(fd, buf, BUFSIZ);

    char *ptr = strtok(buf, " ");
    while(ptr != NULL){
        arr[i++] = ptr;
        ptr = strtok(NULL, " ");
    }
    printf("%s", arr[3]);
    // for(int i = 1; i < 4; i++) {
    //     sum += atoi(arr[i]);
    // }
    // printf("%s %.2lf\n", arr[0], sum/3.0);
    // sum = 0.0;

    // for(int i = 4; arr[i] != NULL; i++) {
    //     sum += atoi(arr[i]);
    // }
    // printf("%s %.2lf\n", arr[3], sum/3.0);

    if(n == -1) perror("read");
    close(fd);
    return 0;
}