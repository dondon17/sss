/***************************************************************************
 *  정리과제 - socket을 이용한 채팅 프로그램 - 서버
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: serv.c
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
#include<netinet/in.h>

#define MAXBUF 1024
#define PORT 8888
int main(int argc, char **argv){

    int server_socket;
    int client_socket;
    int clilen;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char recvbuf[MAXBUF];
    char sendbuf[MAXBUF];
    int recvlen;

    // 1. server 소켓 생성
    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }
    // 주소 초기화
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // 2. 서버 소켓에 주소 연결
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        perror("bind");
        exit(1);
    }

    // 3. 연결 요청 기다림
    if(listen(server_socket, 5) == -1){
        perror("listen");
        exit(1);
    }

    printf("waiting for client...\n");

    // 4. 연결 요청 수락
    clilen = sizeof(client_addr);
    if((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &clilen)) == -1){
        perror("accept");
        exit(1);
    }

    while(1){
        // 데이터 수신
        if((recvlen = recv(client_socket, recvbuf, MAXBUF-1, 0)) == -1){
            perror("recv");
            exit(1);
        }

        if(recvlen == 0) break;

        recvbuf[recvlen] = '\0';

        printf("recived from client << %s\n", recvbuf);
        printf("send >> ");
        // 데이터 전송
        fgets(sendbuf, MAXBUF, stdin);
        if(send(client_socket, sendbuf, strlen(sendbuf), 0) != strlen(sendbuf)){
            perror("send");
            exit(1);
        }
    }
    close(client_socket);
    close(server_socket);
    return 0;
}