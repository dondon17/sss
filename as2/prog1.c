/**************************************************************
 *  실습과제 2 - 입력받은 파일의 접근권한을 수정할 수 있는 프로그램 
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog1.c
 *  작성일: 2020 / 04 / 17
 *  마감일: 2020 / 04 / 22
**************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc, const char *argv[]){
    struct stat buf;
    char op[3]; // operand(u, g, o, r, w, x)와 operator(+, -)가 저장될 문자 배열
    // 명령행 인자가 form에 맞지 않는 경우 종료
    if(argc != 3){
        printf("input arguments are not matching\n");
        exit(1);
    }
    // stat 함수로 전달된 파일명의 상태를 buf에 저장
    stat(argv[2], &buf);
    strcpy(op, argv[1]); // argv[1]로 전달된 식을 하나하나 문자로 저장하기 위한 작업

    // 권한을 추가하는 경우에는 or 연산(|)으로 추가
    if(op[1] == '+'){
        if(op[0] == 'u'){
            if(op[2] == 'r') buf.st_mode |= S_IRUSR;
            if(op[2] == 'w') buf.st_mode |= S_IWUSR;
            if(op[2] == 'x') buf.st_mode |= S_IXUSR;
        }
        if(op[0] == 'g'){
            if(op[2] == 'r') buf.st_mode |= S_IRGRP;
            if(op[2] == 'w') buf.st_mode |= S_IWGRP;
            if(op[2] == 'x') buf.st_mode |= S_IXGRP;
        }
        if(op[0] == 'o'){
            if(op[2] == 'r') buf.st_mode |= S_IROTH;
            if(op[2] == 'w') buf.st_mode |= S_IWOTH;
            if(op[2] == 'x') buf.st_mode |= S_IXOTH;
        }
    }
    // 권한을 해제하는 경우 권한비트에 not연산(~)을 시켜준뒤 전체 권한에 AND연산(&) 수행
    if(op[1] == '-'){
         if(op[0] == 'u'){
            if(op[2] == 'r') buf.st_mode &= ~(S_IRUSR);
            if(op[2] == 'w') buf.st_mode &= ~(S_IWUSR);
            if(op[2] == 'x') buf.st_mode &= ~(S_IXUSR);
        }
        if(op[0] == 'g'){
            if(op[2] == 'r') buf.st_mode &= ~(S_IRGRP);
            if(op[2] == 'w') buf.st_mode &= ~(S_IWGRP);
            if(op[2] == 'x') buf.st_mode &= ~(S_IXGRP);
        }
        if(op[0] == 'o'){
            if(op[2] == 'r') buf.st_mode &= ~(S_IROTH);
            if(op[2] == 'w') buf.st_mode &= ~(S_IWOTH);
            if(op[2] == 'x') buf.st_mode &= ~(S_IXOTH);
        }
    }
    // 바뀐 permission mode를 파일에 적용
    chmod(argv[2], buf.st_mode);
    return 0;
}