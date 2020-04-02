#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    symlink("unix.txt", "unix.sym");
    return 0;    
}