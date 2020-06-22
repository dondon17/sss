/***************************************************************************
 *  정리과제 - socket을 이용한 채팅 프로그램 - 클라이언트
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: cli.c
 *  작성일: 2020 / 06 / 01
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netdb.h>
#include<arpa/inet.h>

#define MAXBUF 1024
#define PORT 8888

int main(int argc, char **argv){

    int client_socket;
    
    char sendbuf[MAXBUF];
    char recvbuf[MAXBUF];
    int recvlen;

    struct sockaddr_in server_addr;

    // 1. socket 생성
    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }
    // 서버 주소 초기화
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);
    
    // 2. 서버에 연결 요청
    if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        perror("connect");
        exit(1);
    }

    while(1){
        printf("send >> ");
        fgets(sendbuf, MAXBUF, stdin);

        if(!strncmp(sendbuf, "q", 1)) break;
        // 3. 메시지 전송
        if(send(client_socket, sendbuf, strlen(sendbuf), 0) != strlen(sendbuf)){
            perror("send");
            exit(1);
        }

        // 4. 메시지 수신
        if((recvlen = recv(client_socket, recvbuf, MAXBUF-1, 0)) <= 0){
            perror("recv");
            exit(1);
        }

        recvbuf[recvlen] = '\0';
        printf("received from server << %s\n", recvbuf);
    }
    

    // 6. 통신 종료
    close(client_socket);

    exit(0);
}