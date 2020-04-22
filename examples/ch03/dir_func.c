#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv){

    char *cwd;
    char wd[BUFSIZ];
    // directory 생성, 삭제, 이름변경 
    // mkdir, rmdir, rename
    if(mkdir("han", 0755) == -1){
        perror("directory han");
        exit(1);
    }

    if(mkdir("bit", 0755) == -1){
        perror("directory bit");
        exit(1);
    }

    if(rename("han", "hanbit") == -1){
        perror("rename han to hanbit");
        exit(1);
    }

    if(rmdir("bit") == -1){
        perror("remove directory bit");
        exit(1);
    }   

    // 현재 작업 directory를 검색하는 방법은 문자열에 getcwd의 리턴값을 저장하던가
    // getcwd의 인자에 문자열 배열을 전달하면 된다.  
    cwd = getcwd(NULL, BUFSIZ);
    printf("1. Current Directory = %s\n", cwd);

    chdir("hanbit");

    getcwd(wd, BUFSIZ);
    printf("2. Current Directory = %s\n", wd);

    return 0;
}