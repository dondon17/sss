/***************************************************************************
 *  정리과제 - pipe를 통해 부모 자식 사이에 메시지 주고받기
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: pipe.c
 *  작성일: 2020 / 06 / 01
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>

int main(void){
    int n;
    int status;
    __pid_t pid;

    char server_buf[BUFSIZ]; // client에게서 받은 메시지를 저장할 버퍼 
    char client_buf[BUFSIZ]; // server에게서 받은 메시지를 저장할 버퍼

    int fd1[2]; // server는 write, client는 read만 하는 파이프
    int fd2[2]; // server는 read, client는 write만 하는 파이프

    // 두 파이프 생성
    if(pipe(fd1) < 0){
        printf("pipe error\n");
        exit(1);
    }
    if(pipe(fd2) < 0){
        printf("pipe error\n");
        exit(1);
    }

    // client 생성
    pid = fork();
    if(pid < 0){
        printf("fork error\n");
        exit(1);
    }
    else if(pid > 0){ // server(parent)
        close(fd1[0]); // 첫번째 파이프의 read 쪽을 닫는다.
        close(fd2[1]); // 두번째 파이프의 write 쪽을 닫는다.
        write(fd1[1], "hello my client", 17); // 첫번째 파이프를 통해 write 연산으로 child에게 보낼 메시지를 입력한다.
        wait(&status);
        n = read(fd2[0], server_buf, BUFSIZ); // 두번째 파이프를 통해 child로부터 받은 메시지를 읽어온다.
        printf("received from client(child): %s\n", server_buf);
    }
    else{
        close(fd1[1]); // 첫번째 파이프의 write 쪽을 닫는다.
        close(fd2[0]); // 두번째 파이프의 read 쪽을 닫는다.
        n = read(fd1[0], client_buf, BUFSIZ); // 첫번째 파이프를 통해 parent로부터 받은 메시지를 읽어온다.
        printf("received from server(parent): %s\n", client_buf);
        write(fd2[1], "hello server", 12); // 두번째 파이프를 통해 write연산으로 parent에게 보낼 메시지를 입력한다.
    }
    exit(0);
}