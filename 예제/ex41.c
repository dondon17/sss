#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(void){
    uid_t uid, euid;
    char *name, *cname="";

    uid = getuid();
    euid = geteuid();

    name = getlogin();
    //cname = cuserid();

    printf("Login name= %s\nUID= %d, EUID= %d\n", name, (int)uid, (int)euid);
    return 0;
}