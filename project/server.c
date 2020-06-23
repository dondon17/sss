#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<arpa/inet.h>
#include<netinet/in.h>

#include<pthread.h>

#define BUFSIZE 1024
#define N_CLIENT 50
#define MAX_IP 30


int count = 0;
int client_sockets[N_CLIENT];
pthread_mutex_t mutex;

// 메시지를 서버에 연결된 모든 클라이언트들에게 전송
void send_msg_func(char *msg, int len){

    // 한 시점에서 한 클라이언트의 메시지만 broadcasting할 수 있음 
    pthread_mutex_lock(&mutex);

    // 소켓 배열에 저장된 클라이언트들에게 메시지 전송
    for(int i=0; i<count; i++){
        write(client_sockets[i], msg, len);
    }

    // 메시지를 모두에게 전송후에 뮤텍스 락 해제
    pthread_mutex_unlock(&mutex);
}
// 연결된 클라이언트들을 마다 쓰레드를 생성하여 처리
void* clients_func(void* soc){
    
    int client_socket = *((int*)soc); // 연결된 소켓을 인자로 전달받아 각 클라이언트 쓰레드 실행
    int len = 0;

    char msg[BUFSIZE];

    while((len = read(client_socket, msg, sizeof(msg))) != 0){
        send_msg_func(msg, len);
    }

    // 채팅방을 나간 클라이언트의 소켓을 제거
    // 마찬가지로 Critical section이므로 뮤텍스락으로 잠그고 시작
    pthread_mutex_lock(&mutex);
    for(int i=0; i<count; i++){
        if(client_socket == client_sockets[i]){
            while(i < count-1){
                // 하나씩 앞으로 당기는 작업(중간에 한 소켓이 나가므로)
                client_sockets[i] = client_sockets[i+1];
                i++;
            }
            break;
        }
    }
    // 클라이언트 수 감소
    count--;
    pthread_mutex_unlock(&mutex);
 
    close(client_socket);

    return NULL;
}

void printserver(char* port){
    system("clear");
    printf("========= SERVER INFO =========\n");
    printf("PORT NUMBER  : %s\n", port);
    printf("MAXIMUN USER : %d\n", N_CLIENT);
    printf("========== WAITING... ==========\n");
}

int main(int argc, char **argv){
    
    int server_socket; // listening socket
    int client_socket; // 실제 연결 소켓

    struct sockaddr_in server_addr; // 서버의 주소 저장
    struct sockaddr_in client_addr; // 연결된 클라이언트 주소 저장

    int client_len; // 연결된 클라이언트 사이즈 저장

    pthread_t th;

    // 명령행 입력 형식에 맞지 않는 경우 종료
    if(argc != 2){
        printf("Enter Port number.\n");
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL); // 사용할 뮤텍스 락 초기화
    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        perror("socket");
        exit(1);
    }
    
    // 주소 초기화
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    printserver(argv[1]);

    // 소켓에 서버 주소 연결
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        perror("bind");
        exit(1);
    }

    // 클라이언트들의 요청 대기큐의 크기를 10으로 지정
    if(listen(server_socket, 10) == -1){
        perror("listen");
        exit(1);
    }
    
    while(1){

        // 수락할 클라이언트의 주소 사이즈 초기화
        client_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if(client_socket == -1){
            perror("accept");
            exit(1);
        }
        // 여러 클라이언트들이 동시에 연결을 요청할 경우, 소켓 배열에 저장되는 클라이언트들의 소켓이 섞일 수 있음
        // 이때 뮤텍스 락을 걸고 연결이 수락된 소켓들을 소켓 배열에 저장
        pthread_mutex_lock(&mutex);
        if(count>N_CLIENT){
            pthread_mutex_unlock(&mutex);
            printf("NO MORE SPACE FOR USER...\n");
            break;
        }
        client_sockets[count++] = client_socket;
        
        pthread_mutex_unlock(&mutex);

        pthread_create(&th, NULL, clients_func, (void*)&client_socket);
        pthread_detach(th); // block되지 않고 Join 기능 수행

        printf("Connected Client's ip > %s\n", inet_ntoa(client_addr.sin_addr));
        printf("Current users(%d/50)\n", count);
    }

    close(server_socket);

    return 0;
}