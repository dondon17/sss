#include<sys/utsname.h>
#include<stdio.h>

int main(void){
    struct utsname uts;

    uname(&uts);

    printf("system name : %s\n", uts.sysname);
    printf("node name   : %s\n", uts.nodename);
    printf("machine     : %s\n", uts.machine);
    printf("version     : %s\n", uts.version);
    printf("release     : %s\n", uts.release);

    return 0;
}