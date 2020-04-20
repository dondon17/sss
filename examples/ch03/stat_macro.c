#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char **argv){
    struct stat buf;

    stat("unix.txt", &buf);

    printf("Mode = %o\n", (unsigned int)buf.st_mode);

    if(S_ISFIFO(buf.st_mode)) printf("unix.txt : FIFO\n");
    if(S_ISDIR(buf.st_mode)) printf("unix.txt : Directory\n");
    if(S_ISREG(buf.st_mode)) printf("unix.txt : Regular file\n");
    return 0;
}

// st.mode & S_IFMT 수행을 통해 파일의 종류를 알아볼 수 있지만
// S_ISFIFO, S_ISDIR, S_ISREG과 같은 st.mode만을 매개변수로 받아 파일의 종류를 알려주는 매크로를 사용할 수도 있다.