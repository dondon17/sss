#include<stdio.h>
#include<stdlib.h>
#include<sys/utsname.h>

int main(void){
    struct utsname uts;

    // stat함수랑 매우 비슷하다. 
    // 매개변수로 utsname 구조체 변수를 받으면 저절로 시스템의 정보를 불러온다.
    if(uname(&uts) == -1){
        perror("uname");
        exit(1);
    }

    printf("OS name : %s\n", uts.sysname);
    printf("Node name : %s\n", uts.nodename);
    printf("Release : %s\n", uts.release);
    printf("Version : %s\n", uts.version);
    printf("Machine : %s\n", uts.machine);

    return 0;
}