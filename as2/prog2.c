/*************************************************************************************  
 *  실습과제 2 - 사용자명을 입력받아 primary group, secondary group을 출력해주는 프로그램
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: prog2.c
 *  작성일: 2020 / 04 / 18
 *  마감일: 2020 / 04 / 22
 *************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<utmpx.h>
#include<grp.h>
#include<pwd.h>
int main(void){
    char name[257];
    struct passwd* pw;

    // 사용자명 입력
    printf("input user name : "); scanf("%s", name);

    // 입력한 사용자가 있으면 passwd 구조체 변수에 해당 사용자 정보 저장 없으면 종료
    if((pw = getpwnam(name)) == NULL){
        printf("%s: no such user\n", name);
        exit(1);
    }

    // 입력한 사용자의 이름 출력
    printf("user : %s\n", pw->pw_name);

    // 사용자가 속한 그룹을 출력 코드
    int n_groups = 0; // 그룹의 수를 저장할 변수 선언 및 초기화
    getgrouplist(pw->pw_name, pw->pw_gid, NULL, &n_groups); // n_groups를 얻어내기 위한 작업
    gid_t groups_gid[n_groups]; // 사용자가 속한 그룹의 gid를 저장할 gid 배열
    
    getgrouplist(pw->pw_name, pw->pw_gid, groups_gid, &n_groups);
    for (int i = 0; i < n_groups; i++){
        // groups_gid에 저장된 gid를 차례대로 사용해 그룹의 정보를 gr에 저장
        struct group* gr;
        if((gr = getgrgid(groups_gid[i]))== NULL) perror("getgrgid error: ");
        
        // Primary group
        if(i==0){
            printf("Primary Group : ");
            printf("%s\n", gr->gr_name);
        }
        // Secondary groups
        else if(i==1){
            printf("Secondary group : ");
            printf("%s ", gr->gr_name);
        }
        else printf("%s ", gr->gr_name);
    }
    printf("\n");
    return 0;
}