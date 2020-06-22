/***************************************************************************
 *  실습과제 6 - 서버에 접속한 클라이언트 정보 보내주기 - server
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: server.c
 *  작성일: 2020 / 06 / 01
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/signal.h>

#include<netinet/in.h>
#include<arpa/inet.h>

#define BUFSIZE 1024
#define PORT 1111

int main(void){

    int server_sockfd; 
    int client_sockfd;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    char recvbuf[BUFSIZE];

    int client_len;
    int recvlen;

    // 1. 소켓 생성
    if((server_sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    // 2. 서버의 정보 초기화
    memset(&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 자동으로 ip주소를 찾아 대입
    server_addr.sin_port = htons(PORT);

    // 3. 서버에서 생성한 소켓에 주소 정보를 연결 - bind
    if(bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        exit(1);
    }

    // 4. 서버 소켓으로 연결을 원하는 클라이언트들의 요청을 기다림 - listen
    if(listen(server_sockfd, 5) == -1) {
        perror("listen failed"); 
        exit(1);
    }

    // 5. 서버에 연결 요청한 클라이언트의 요청 수락 - accept
    int count  = 0;
    client_len = sizeof(client_addr);
    if((client_sockfd=accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len)) == -1) {
        perror("accept failed");
        exit(1);
    }    

    while(1) {
        // 6. 연결된 클라이언트의 소켓으로 들어오는 정보를 버퍼에 저장 - recv
        if((recvlen=recv(client_sockfd, recvbuf, BUFSIZE-1, 0)) == -1) {
            perror("recv failed");
            exit(1);
        }
        if(recvlen == 0) break;
        
        recvbuf[recvlen] = '\0'; // 버퍼에 계속 쌓이는 것을 방지
        
        printf("Client Info - %s\n", recvbuf);
        
        // 7. 받은 데이터를 클라이언트에게 보냄 - send
        if(send(client_sockfd, recvbuf, recvlen, 0) != recvlen) {
            perror("send failed");
            exit(1);
        }
    }
    // 8. 연결이 끝난 클라이언트와의 소켓을 닫음
    close(client_sockfd);
    close(server_sockfd);

    return 0;
}
