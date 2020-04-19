#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(int argc, char **argv)
{
    int fdout, fdin;
    if((fdout = open("out.txt", O_CREAT | O_RDWR | O_TRUNC, 0644)) == -1){
       perror("open");
       exit(1);
    }

    if((fdin = open("in.txt", O_CREAT | O_RDWR, 0644)) == -1){
       perror("open");
       exit(1);
    }

    // 자식에게만 표준 입출력이 redirection된 상태로 전달시키고
    // 부모는 다시 키보드와 모니터를 표준 입/출력으로 사용하기 위해 임시 저장
    int fdtmp_stdin = dup(STDIN_FILENO); 
    int fdtmp_stdout = dup(STDOUT_FILENO); 

    // 본격적으로 지정한 파일들을 표준 출력, 입력으로 사용
    dup2(fdout, STDOUT_FILENO); 
    dup2(fdin, STDIN_FILENO);
    dup2(1, 2); // 표준 err도 fdout 파일로 변경해줌.
    
    // 자식에게 redirection된 표준 입/출력을 그대로 전달
    pid_t pid = fork();
    if(pid > 0){ // 부모 프로세스
        int stat=0;
        wait(&stat);
    }
    else if(pid == 0){ // 자식 프로세스
        char *buf;
        int n;
        puts("standard out is out.txt file in child!\n");
        //execlp("ls", "ls", "-a", (char*)NULL);
        exit(0);
    }
    else{ // fork 실패
        perror("fork");
        exit(1);
    }
    // 표준 입/출력으로 사용된 파일들을 닫아줌
    close(fdout); 
    close(fdin);

    // 부모프로세스에서는 처음대로 키보드와 모니터가 각각 표준 입/출력으로 다시 설정됨 
    dup2(fdtmp_stdout, STDOUT_FILENO);
    close(fdtmp_stdout); 

    dup2(fdtmp_stdin, STDIN_FILENO);
    close(fdtmp_stdin);

    puts("standard output is monitor in parent!\n");
    return 0;
}
