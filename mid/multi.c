#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/types.h>

#define N_CHILD 4

int arr[100000] = {0, };

int main(void){
    clock_t start, end;
    FILE *a, *b, *c, *d;
    pid_t pid[N_CHILD];

    double time_spent, res = 0, sum[4] = {0, };
    
    int status;
    // 타이머 시작
    printf("***Timer start***\n"); 
    start = clock();

    for(int i=0; i<N_CHILD; i++){
        pid[i] = vfork(); // fork 열었을 시 부모 프로세스의 변수들을 공유하지 않아 vfork로 생성
        if(pid[i] < 0){
            perror("fail");
            exit(1);
        }
        else if(pid[i] == 0){
            switch (i) {
                case 0: 
                    if((a=fopen("a.txt", "r")) == NULL){
                        perror("a.txt");
                        exit(1);
                    }
                    for(int i=0; i<100000; i++) {
                        fscanf(a, "%d ", &arr[i]);
                        sum[0] += arr[i];
                    }
                    exit(0);
                    break;

                case 1:
                    if((b=fopen("b.txt", "r")) == NULL){
                        perror("b.txt");
                        exit(1);
                    }
                    for(int i=0; i<100000; i++) {
                        fscanf(b, "%d ", &arr[i]);
                        sum[1] += arr[i];
                    }
                    exit(1);
                    break;

                case 2:
                    if((c=fopen("c.txt", "r")) == NULL){
                        perror("c.txt");
                        exit(1);
                    }
                    for(int i=0; i<100000; i++) {
                        fscanf(c, "%d ", &arr[i]);
                        sum[2] += arr[i];
                    }    
                    exit(2);
                    break;

                case 3:
                    if((d=fopen("d.txt", "r")) == NULL){
                        perror("d.txt");
                        exit(1);
                    }
                    for(int i=0; i<100000; i++) {
                        fscanf(d, "%d ", &arr[i]);
                        sum[3] += arr[i];
                    }
                    exit(3);
                    break;
            }
        }
    }
    
    // 자식프로세스들의 종료상태를 정상적으로 처리하는지 확인하기 위해 출력
    int pid_;
    for(int i=0; i<N_CHILD; i++) {
        pid_ = wait(&status);
        printf("child %ld exited...(status: %d)\n", (long)pid_, status); 
    }

    // 각각의 파일에서 구한 sub sum들을 모두 총합
    for(int i=0; i<4; i++) res+=sum[i];
    printf("%f\n", res);
    printf("***Timer end***\n");
    end = clock();
    
    time_spent = (double)(end - start);
    printf("time: %f\n", time_spent);
    return 0;
}