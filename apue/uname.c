#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/utsname.h>

int main(void){

    // utsname 구조체 포인터 변수가 아닌 그냥 구조체 변수로 선언
    struct utsname uts;
    
    // 구조체 변수의 주소값 전달
    uname(&uts);

    printf("system name : %s\n", uts.sysname);
    printf("node name : %s\n", uts.nodename);
    printf("release : %s\n", uts.release);
    printf("version : %s\n", uts.version);
    printf("machine : %s\n", uts.machine);
    return 0;

}