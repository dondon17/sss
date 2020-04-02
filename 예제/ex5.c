#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int n;
    extern char *optarg;
    extern int optind;

    printf("current optind: %d\n", optind);
    while((n=getopt(argc, argv, "abc:")) != -1){
        switch (n)
        {
        case 'a':
            printf("option : a\n");
            break;
        case 'b':
            printf("option : b\n");
            break;
        case 'c':
            printf("option : c, argument = %s\n", optarg);
            break;
        }
        printf("next optind : %d\n", optind);
    }
    return 0;
}
// #include<unistd.h>
// int getopt(int argc, char* const argv[], const char *optstring)
// 옵션 처리 함수
// 명령어 뒤에 오는 옵션을 처리하는 함수로 예제에서는 간단하게 switch문으로 해당 출력물을 출력한다.