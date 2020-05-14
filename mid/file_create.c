#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    FILE *a, *b, *c, *d; 

    int arr[100000] = {0, }; // 각각의 파일에서 10만개의 수를 읽어오기 위함

    if((a=fopen("a.txt", "w")) == NULL){
        perror("a.txt");
        exit(1);
    }
    if((b=fopen("b.txt", "w")) == NULL){
        perror("b.txt");
        exit(1);
    }
    if((c=fopen("c.txt", "w")) == NULL){
        perror("c.txt");
        exit(1);
    }
    if((d=fopen("d.txt", "w")) == NULL){
        perror("d.txt");
        exit(1);
    }    

    for(int i=0; i<100000; i++) {
        arr[i] = i+1;
        fprintf(a, "%d ", arr[i]);
    }
    fclose(a);

    for(int i=0; i<100000; i++) {
        arr[i] = i+100001;
        fprintf(b, "%d ", arr[i]);
    }
    fclose(b);

    for(int i=0; i<100000; i++) {
        arr[i] = i+200001;
        fprintf(c, "%d ", arr[i]);
    }
    fclose(c);    
    for(int i=0; i<100000; i++) {
        arr[i] = i+300001;
        fprintf(d, "%d ", arr[i]);
    }
    fclose(d);        
    return 0;
}