#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<signal.h>
#include<setjmp.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<termios.h>

#define N_TRY 5

jmp_buf checkpoint; // setjmp의 백업포인트

int try_count = 1; // 시도 횟수로 사용할 변수

// 미리 지정해둔 아이디와 비밀번호
const char *userid = "dondon";
const char *userpasswd = "dondon4557";

// 비밀번호 마스킹을 위한 함수로 리눅스에서는 conio.h를 제공해주지 않는다고 하여 구현
int getch(void){
    int ch;
    struct termios buf, save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}

// 입력한 id와 비밀번호를 미리 지정해둔 id와 비밀번호와 비교
int checkuser(char *id, char* pwd){
    if(!strcmp(userid, id) && !strcmp(userpasswd, pwd)) return 1;
    // 올바르지 않은 아이디와 비밀번호인 경우 시도 회수를 증가시키고 입력창으로 점프
    else {
        printf("login failed...(%d try left...)\n", N_TRY-try_count);
        try_count++;
        longjmp(checkpoint, 200);
    }
}

// 30초 이내에 id와 비밀번호를 입력하지 않은 경우
void alarm_handler(int signo){
    if(signo == SIGALRM) {
        printf("Timer expired. Please try again after 10 minutes.\n");
        sleep(10); // 10분 동안 sleep하려면 600으로 설정해야하지만 시간이 너무 오래 걸리므로 10초로 설정했습니다.
        longjmp(checkpoint, 100); // 다시 입력창(아이디 패스워드 입력하는 부분)으로 점프
    }
}

void reset_count(){
    // 시도회수 초기화 후 입력창으로 점프
    try_count = 1;
    longjmp(checkpoint, 300);
}

void login_handler(int signo){
    // 입력할 아이디, 비밀번호
    char inputid[BUFSIZ];
    char inputpwd[BUFSIZ];

    // sigaction 함수를 사용해 SIGALRM에 대한 핸들러 지정
    struct sigaction sa;
    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGALRM);
    sigaction(SIGALRM, &sa, 0);

    // 받은 시그널이 SIGUSR1인 경우 아래 코드 실행
    if(signo == SIGUSR1){
        printf("***login program***\n");

        // 점프 지점으로 올 때마다 알람을 재설정
        if(setjmp(checkpoint) > 0) alarm(0); 

        // 시도횟수가 5회 이하인 경우
        if(try_count <= 5){
            alarm(30);
            printf("ID       : ");
            gets(inputid);
            fflush(stdin); // 입력 버퍼를 비워줘야 이상하게 출력이 안됨

            printf("Password : ");
            gets(inputpwd);
            fflush(stdin);
            
            alarm(0); // 30초 내에 입력한 경우 알람을 초기화

            // 입력한 아이디와 비밀번호를 비교해 올바른 아이디, 비밀번호인 경우 프로그램 종료
            // 올바르지 않는 경우 checkuser 함수에서 try_count 변수를 1씩 증가
            if(checkuser(inputid, inputpwd)){ 
                printf("login success!\n");
                exit(0);
            }
        }

        // 시도 회수가 5회를 넘으면 10분동안 sleep후 시도 횟수를 초기화하는 reset_count함수를 호출
        // reset_count 함수에서는 try_count 변수를 1로 초기화하고, longjmp를 통해 setjmp위치로 이동
        else{
            printf("you failed 5 times...\n");
            printf("Try again after 10 minutes...\n");
            sleep(10); // 원래는 600으로 설정해야하지만 시간상 10초로 설정하였습니다.
            reset_count();
        }

    }
}

int main(void){
    pid_t ppid = getpid(); // 부모프로세스의 pid를 담아둘 변수 선언 및 초기화
    pid_t pid;

    pid = fork();

    // fork 실패 시
    if(pid < 0){
        perror("fork fail");
        exit(1);
    }
    // 자식 프로세스에서 kill 함수를 통해 부모프로세스에게 Login 프로그램을 실행하도록 핸들러가 작성된 SIGUSR1 시그널 전송
    else if(pid == 0){
        kill(ppid, SIGUSR1);
    }
    // 부모 프로세스에서는 자식에게서 SIGUSR1 시그널 오기까지 pause를 통해 대기
    else{
        while(1){
            if(signal(SIGUSR1, login_handler) == SIG_ERR){
                perror("signal");
                exit(1);
            }
            pause();
        }
    }

    return 0;
}