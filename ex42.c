#include<stdio.h>
#include<unistd.h>
#include<pwd.h>

int main(void){
    struct passwd *pw;

    // pw = getpwuid(getuid());
    // printf("UID : %d\n", (int)pw->pw_uid);
    // printf("Login Name : %s\n", pw->pw_name);

    pw = getpwnam("kkkkk");
    printf("UID : %d\n", (int)pw->pw_uid);
    printf("Home Directory : %s\n", pw->pw_dir);

    return 0;
}