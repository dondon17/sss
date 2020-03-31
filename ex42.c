#include<stdio.h>
#include<unistd.h>
#include<pwd.h>

int main(void){
    struct passwd *pw;

    pw = getpwuid(getuid());
    printf("UID : %d\n", (int)pw->pw_uid);
    printf("Login Name : %s\n", pw->pw_name);

    // pw = getpwnam("kkkkk");
    // printf("UID : %d\n", (int)pw->pw_uid);
    // printf("Home Directory : %s\n", pw->pw_dir);

    for(int i=0; i < 3; i++){
        pw = getpwent();
        printf("uid : %d, login name : %s\n", (int)pw->pw_uid, pw->pw_name);
    }
    return 0;
}