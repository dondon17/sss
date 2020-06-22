/***************************************************************************
 *  정리과제 - non blocking I/O
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: nonblock.c
 *  작성일: 2020 / 06 / 03
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<wait.h>
#include<errno.h>

int errno;

int main(void){
    int pipe_fd[2];
    pid_t pid;
    int status;

    // pipe 생성
    if(pipe(pipe_fd) < 0){
        perror("create pipe failed");
        exit(1);
    }

    // pipe의 read 부분을 non blocking 모드로 설정
    if(fcntl(pipe_fd[0], F_SETFL, O_NONBLOCK) < 0){
        perror("setting read pipe in Non Blocking mode");
        exit(1);
    }

    pid = fork();
    if(pid < 0){
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0){
        char *msg = "hello parent.";
        close(pipe_fd[0]);
        
        // 2초마다 파이프를 통해 부모에게 메시지 전송
        // 2초마다 보내는 이유는 그 2초동안 부모가 Non block 상태인지 확인하기 위함
        for(int i=0; i<3; i++){
            write(pipe_fd[1], msg, strlen(msg));
            sleep(2);
        }

        // 종료 문구 전송 후 종료
        write(pipe_fd[1], "close pipe...\n", BUFSIZ);
        exit(0);
    }
    else{
        close(pipe_fd[1]);
        
        while(1){
            char buf[BUFSIZ];
            int n = read(pipe_fd[0], buf, BUFSIZ);
            switch (n)
            {
            case -1:
                if(errno == EAGAIN){
                    // pipe가 non block 모드이므로 읽어올 것이 없을 때 block 되지 않고, 
                    // EAGAIN 오류 코드를 출력
                    printf("empty...\n");
                    sleep(1);
                    break;
                }
                else{
                    // 위의 에러코드가 아닌 경우는 READ를 실패한 경우이므로 종료
                    perror("read");
                    exit(1);
                }
            case 0:
                // 읽어올 것이 없는 경우 0을 반환하고 종료
                printf("no more messages to read... end program...\n");
                close(pipe_fd[0]);
                exit(0);
            default:
                // 파이프를 통해 수신한 메시지 출력
                printf("received from child >> %s\n", buf);
            }
        }
    }
}