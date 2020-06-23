#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<arpa/inet.h>
#include<netinet/in.h>

#include<pthread.h>
#include<time.h>

#define BUFSIZE 1024

#pragma warning(disable:4996)

char *username;
char *connect_ip;
char *connect_port;
char *msg;

// 함수 선언부
void* send_th_func(void *soc);
void* recv_th_func(void *soc);
char* time_stamp();
void print_Manual();
void select_Menu();
void change_Name();

// 메인함수
int main(int argc, char **argv){
    
    int client_socket; // 채팅 서버에 연결할 소켓
    struct sockaddr_in server_addr; // 서버 주소 초기화할 주소 

    pthread_t send_thread, recv_thread; // non-blocking 모드로 채팅하기 위해 송신 쓰레드와 수신 쓰레드 사용
    void* tret; // 쓰레드 반환값 저장
    
    // 사용자는 명령행에 연결할 서버(local host)의 IP주소, 열린 포트 번호, 채팅방에 입장할 이름 순으로 입력
    if(argc != 4){
        printf("Enter 1. ip number, 2. port number, and 3. your name...\n");
        exit(1);
    }

    // 문자열 포인터 사이즈 및 변수 초기화
    connect_ip = (char*)malloc(sizeof(char)*(strlen(argv[1])+1));
    connect_port = (char*)malloc(sizeof(char)*(strlen(argv[2])+1));
    username = (char*)malloc(sizeof(char)*(strlen(argv[3])+2));
    
    sprintf(connect_ip, "%s", argv[1]);
    sprintf(connect_port, "%s", argv[2]);
    sprintf(username, "[%s]", argv[3]);
   
    // 채팅 서버에 연결할 소켓 생성
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        perror("socket");
        exit(1);
    }

    // 명령행으로 입력받은 서버의 ip주소와 연결할 포트번호로 서버 주소 초기화
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // 서버에 연결 시도
    if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        perror("connect");
        exit(1);
    }

    // 채팅방 메뉴얼 출력
    print_Manual();

    // 메시지 송신 쓰레드 생성 - 인자로 소켓 전달
    if(pthread_create(&send_thread, NULL, send_th_func, (void*)&client_socket) != 0){
        perror("create send thread");
        exit(1);
    }
    // 메시지 수신 쓰레드 생성 - 인자로 소켓 전달
    if(pthread_create(&recv_thread, NULL, recv_th_func, (void*)&client_socket) != 0){
        perror("create recv thread");
        exit(1);
    }

    // thread 종료 상태 대기
    pthread_join(send_thread, &tret);
    pthread_join(recv_thread, &tret);

    // 소켓 닫고 통신 종료
    close(client_socket);
    
    return 0;
}

// 전송 시간을 나타낼 타임스탬프 생성
char* time_stamp(){
    char* loctime = (char*)malloc(sizeof(char)*16);
    time_t now;
    now = time(NULL);
    struct tm *tm;
    tm = localtime(&now);
    sprintf(loctime, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min, tm->tm_sec);
    return loctime;
}

// 메뉴얼 창 출력
void print_Manual(){

    system("clear");

    printf("========= USER / SERVER INFO =========\n");
    printf("Chat Server IP  : %s\n", connect_ip);
    printf("Chat Server PORT: %s\n", connect_port);
    printf("Chat User Name  : %s\n\n", username);

    printf("=============== MANUAL ===============\n");
    printf("To see Manual, enter > man\n");
    printf("To change Name, enter > 1\n");
    printf("To clear log, enter > 2\n");
    printf("To exit chatting room, enter q or Q\n");
    printf("======================================\n\n");

}

void select_Menu(){
    int choice;

    printf("\n\t====== SELECT MENU ======\n");
    printf("\tChange Name : 1\n");
    printf("\tClear Log   : 2\n");
    printf("\tBack to chat: enter any key\n");
    printf("\t===========================\n");
    printf("\tenter >> "); scanf("%d", &choice);
    getchar();

    switch (choice){
    case 1:
        change_Name();
        break;
    case 2:
        system("clear");
        printf("log cleared...\n");
        break;
    default:
        printf("Continue chatting...\n\n");
        break;
    }
}

// 이름 변경 함수
void change_Name(){
    char temp[20];
    printf("\n\tNew Name >> "); 
    scanf("%s", temp);
    sprintf(username, "[%s]", temp);
    printf("\n\tName changed to [%s].\n", temp);
}

// 송신 기능 쓰레드
void *send_th_func(void *soc){

    int client_socket = *((int*)soc); // 쓰레드 생성시 생성 및 연결된 소켓을 인자로 전달
    char leave_msg[BUFSIZE];
    char client_msg[BUFSIZE]; // 사용자 이름, 메시지 내용, 보낸 시간을 합친 문자열
    char userinfo[64];
    char *msg_time = (char*)malloc(sizeof(char)*10); // 메시지 입력 시간 출력
    msg = (char*)malloc(sizeof(char)*257); // 입력 메시지
    char *ans = (char*)malloc(sizeof(char)*3);
    sprintf(userinfo, "%s joined the room.\n", username);
    send(client_socket, userinfo, strlen(userinfo), 0);

    printf("You entered the chatting room.\n");

    while(1){
        
        fgets(msg, BUFSIZE, stdin);
        msg_time = time_stamp();
        // man 입력 시 메뉴얼 페이지 open
        if(!strcmp(msg, "man\n")){
            select_Menu();
            continue;
        }

        // q나 Q 입력 시 열었던 소켓을 닫고 통신 종료
        else if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")){
            fflush(stdin);
            printf("Do you want to exit the room? > ");
            fgets(ans, sizeof(ans), stdin);
            if(!strcmp(ans, "Y\n") || !strcmp(ans, "y\n")){
                fflush(stdin);
                sprintf(leave_msg, "%s%s", username, " left the room\n");
                send(client_socket, leave_msg, strlen(leave_msg), 0);
                close(client_socket);
                exit(1);
            }
            else{
                fflush(stdin);
                printf("continue chat...\n");
            }
            
        }

        // 입력 메시지가 q나 man이 아닌 경우 사용자의 이름과 입력한 메시지를 함께 전송
        else{
            sprintf(client_msg, "%s[%s]%s", username, msg_time, msg);
            send(client_socket, client_msg, strlen(client_msg), 0);
        }
    }

    return NULL;
}

// 수신 쓰레드
void *recv_th_func(void *soc){
    
    int client_socket = *((int*)soc);
    char client_msg[BUFSIZE];
    ssize_t len;

    while(1){
        len = recv(client_socket, client_msg, BUFSIZE-1, 0);
        if(len == -1) return (void*)-1;

        client_msg[len] = 0;
        fputs(client_msg, stdout);
    }

    return NULL;
}   