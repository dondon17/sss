/***************************************************************************
 *  정리과제 - pthread barrier
 *  이  름: 김도운
 *  학  과: 사이버보안학과
 *  학  번: 201520893
 *  파일명: barrier.c
 *  작성일: 2020 / 06 / 03
 *  마감일: 2020 / 06 / 10
 ***************************************************************************/
#include<stdlib.h>
#include<stdio.h> 
#include<string.h>
#include<unistd.h>
#include<pthread.h> 
#include<time.h>

// 장벽에서 대기할 쓰레드의 개수를 5로 설정
#define THREAD_NUM 5
// 사용할 장벽 변수 선언
pthread_barrier_t barrier;

void *func(void *argv){
    char *name = (char*)argv;
    int rnum[6];
    printf("%s is creating random number...\n", name);
    srand(time(NULL));
    for(int i=0; i<6; i++){
        rnum[i] = rand()%45 + 1;
    }
    printf("%s created random numbers and waiting for other barriers...\n", name);

    // 쓰레드들은 위 작업을 수행한뒤 계속 진행하지 않고 장벽에서 대기
    // 장벽에 모든 5개의 쓰레드들이 도착하면 아래 작없 수행
    pthread_barrier_wait(&barrier);

    // 장벽에 도달해야하는 쓰레드 수가 만족되면 아래 문구 출력
    printf("%s >> ", name);
    for(int i=0; i<6; i++) {
        if(i==5) printf("%d\n", rnum[i]);
        else printf("%d ", rnum[i]);
    }
    
}

int main(int argc, char **argv){
    pthread_t t[THREAD_NUM];
    char name[THREAD_NUM][10] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4", "Thread 5"};
    
    // 장벽 초기화
    pthread_barrier_init(&barrier, NULL, THREAD_NUM);

    for(int i=0; i<THREAD_NUM; i++){
        pthread_create(&t[i], NULL, func, (void*)name[i]);
        sleep(1);
    }
    // 메인 쓰레드에서도 barrier_wait로 기다릴 수 있으며, 이 때는 main thread를 포함하므로
    // 장벽에서 대기할 쓰레드 개수를 1 늘려줘야됨
    // join을 사용하는 경우 위 작업 필요없음
    for(int i=0; i<THREAD_NUM; i++) pthread_join(t[i], NULL);

    printf("All thread end\n");

    // 장벽 폐기
    pthread_barrier_destroy(&barrier);

    return 0;
}