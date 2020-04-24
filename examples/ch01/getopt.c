#include<stdio.h>

int main(int argc, char **argv){
    int n;
    extern char *optarg;
    extern int optind;

    printf("Current Optind : %d\n", optind);
    while((n = getopt(argc, argv, "abc:")) != -1){
        switch (n){
        case 'a':
            printf("option : a\n");
            break;
        case 'b':
            printf("option : b\n");
            break;
        case 'c':
            printf("option : c\targument : %s\n", optarg);
            break;    
        }
        printf("Next Optind : %d\n", optind);
    }

    return 0;
}

// 옵션 처리함수 : getopt
// 명령어의 옵션은 합쳐져서 사용될 수 있다. 
// 예를 들어, ls -a와 ls -l은 ls-al로 합쳐질 수 있는데, 이 때 옵션들을 구분시켜 각각의 동작을 수행해야한다.
// getopt 함수를 통해 옵션에는 a, b, 그리고 c가 있으며 특히 c 옵션은 뒤에 argument가 추가로 입력되야 하는 옵션이다.