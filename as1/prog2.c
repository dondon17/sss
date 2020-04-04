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
    for(int i=0; i<n; i++){
        if(buf[i] == '\n')
            buf[i] = ' ';
    }

    char *ptr = strtok(buf, " ");
    while(ptr != NULL) {
        arr[i] = ptr;
        ptr = strtok(NULL, " ");
        i++;
    }

    printf("   학번   평균   \n");
    for(int i=0; i<4; i++){
        if(i==0) printf("%s : ", arr[i]);
        else sum += atoi(arr[i]);
    }
    printf("%.2lf\n", sum/3.0);
    sum = 0;

    for(int i=4; i<8; i++){
        if(i==4) printf("%s : ", arr[i]);
        else sum += atoi(arr[i]);
    }
    printf("%.2lf\n", sum/3.0);

    close(fd);
    return 0;
}