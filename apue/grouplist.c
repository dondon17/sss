#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<grp.h>
#include<fcntl.h>
#include<pwd.h>
#include<string.h>
#include "apue.h"

int main(void){
    struct passwd* pw;

    if((pw = getpwnam("dondon")) == NULL){
        perror("dondon");
        exit(1);
    }

    int n = 0;

    getgrouplist(pw->pw_name, pw->pw_gid, NULL, &n);
    gid_t groups_gid[n];

    getgrouplist(pw->pw_name, pw->pw_gid, groups_gid, &n);

    for(int i=0; i<n; i++){
        struct group* gr;
        if((gr = getgrgid(groups_gid[i])) == NULL) perror("getgrgrid error:");

        printf("%s ", gr->gr_name);
    }
    printf("\n");
    return 0;
}
