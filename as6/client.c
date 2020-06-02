#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#define BUFSIZE 1024

int main(int argc, char **argv){

    int client_sockfd;
    char *PORT = "1111"; // 사용할 포트번호이며, 2차원 문자열 배열에 append시키기 위해 문자열 포인터로 선언

    struct sockaddr_in server_addr; // 연결할 서버의 정보를 설정할 구조체 변수 선언

    char sendbuf[BUFSIZE]; // 소켓을 통해 서버로 보낼 메시지를 저장하는 버퍼
    char recvbuf[BUFSIZE]; // 소켓을 통해 서버에게 받은 메시지를 저장하는 버퍼

    int recvlen;
    int i = 0;

    // 전달할 메시지들
    char info[3][128] = {"Host name : ", "IP Address : ", "Port Number : "};
    char hostname[80];
    char *ipbuffer;
    struct hostent *host_entry;

    gethostname(hostname, sizeof(hostname)); // 호스트 명을 확인하여 hostname 변수에 저장
    host_entry = gethostbyname(hostname); // hostent 구조체의 정보들을 얻은 호스트의 정보들로 채움
    ipbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0])); // hostent의 ip주소에 해당하는 요소를 따로 저장
 
    // 입/출력 형식을 맞추기 위해 미리 초기화해둔 2차원 문자열 배열에 호스트명, ip주소, 포트 번호를 append
    strcat(info[0], hostname); 
    strcat(info[1], ipbuffer);
    strcat(info[2], PORT);


    // 1. 소켓 생성
    if((client_sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("sock failed");
        exit(1);
    }


    // 연결할 서버 정보 초기화
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // IPv4주소를 사용
    server_addr.sin_port = htons(atoi(PORT)); // 지정해둔 포트번호 7777을 정수로 변환해서 설정
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 로컬 호스트(자기 자신)을 나타내는 ip주소로 설정
    
    // 2. 설정한 서버에 통신을 요청
    if(connect(client_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    while(1) {
        if(i > 2) break; // 전달할 데이터가 더 이상 없으므로 break;
        
        // 3. 데이터 전송 - send
        // sockfd 소켓을 통해 보낼 데이터는 sendbuf에 복사하여 send 함수를 통해 전달
        strcpy(sendbuf, info[i++]);
        if(send(client_sockfd, sendbuf, strlen(sendbuf), 0) != strlen(sendbuf)) {
            perror("send failed");
            exit(1);
        }

        // 4. 데이터 수신 - recv
        // sockfd 소켓을 통해 받은 데이터는 recv함수를 호출하여 recvbuf에 저장
        if((recvlen=recv(client_sockfd, recvbuf, BUFSIZE-1, 0)) <= 0) {
            perror("recv failed");
            exit(1);
        }   
        recvbuf[recvlen] = '\0'; // 마지막 문자를 널로 초기화하여 버퍼에 쌓이는 것을 방지
        printf("Get from server - My %s\n", recvbuf);                       
    }
    // 5. 사용이 끝난 소켓을 닫음 
    close(client_sockfd);

    exit(0);
}

