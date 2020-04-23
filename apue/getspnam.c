#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<shadow.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    struct spwd *sp;

    if((sp = getspnam("dondon")) == NULL){
        perror("dondon");
        exit(1);
    }

    printf("user name   : %s\n", sp->sp_namp);
    printf("user passwd : %s\n", sp->sp_pwdp);

    return 0;
}