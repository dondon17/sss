#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    clock_t start, end; // 수행시간 제기 위한 clock 변수
    FILE *a, *b, *c, *d; 
    double time_spent; // 소요된 시간 저장
    double sum = 0;
    int arr[100000] = {0, }; // 각각의 파일에서 10만개의 수를 읽어오기 위함
    // timer start
    printf("***Timer start***\n");
    start = clock();

    if((a=fopen("a.txt", "r")) == NULL){
        perror("a.txt");
        exit(1);
    }
    if((b=fopen("b.txt", "r")) == NULL){
        perror("b.txt");
        exit(1);
    }
    if((c=fopen("c.txt", "r")) == NULL){
        perror("c.txt");
        exit(1);
    }
    if((d=fopen("d.txt", "r")) == NULL){
        perror("d.txt");
        exit(1);
    }    
    
    // 각각의 파일을 순서대로 읽어 합계 계산
    for(int i=0; i<100000; i++) {
        fscanf(a, "%d ", &arr[i]);
        sum += arr[i];
    }
    fclose(a);
    for(int i=0; i<100000; i++) {
        fscanf(b, "%d ", &arr[i]);
        sum += arr[i];
    }
    fclose(b);
    for(int i=0; i<100000; i++) {
        fscanf(c, "%d ", &arr[i]);
        sum += arr[i];
    }
    fclose(c);
    for(int i=0; i<100000; i++) {
        fscanf(d, "%d ", &arr[i]);
        sum += arr[i];
    }
    fclose(d);

    printf("total sum : %f\n", sum);
    // timer end...
    end = clock();
    printf("***Timer end***\n");
    time_spent = (double)(end - start);
    printf("time: %f\n", time_spent);
    return 0;
}