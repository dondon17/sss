#include<unistd.h>
#include<stdio.h>

int main(void){
    printf("Link MAX : %ld\n", pathconf(".", _PC_LINK_MAX));
    printf("Name MAX : %ld\n", pathconf(".", _PC_NAME_MAX));
    printf("Path MAX : %ld\n", pathconf(".", _PC_PATH_MAX));

    return 0;
}