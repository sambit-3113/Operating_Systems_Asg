#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int sum;
void *add(void *arr){
        int *a = (int *)arr;
        sum = a[0] + a[1];
}

int main(){
        int arr[2];
        printf("Enter two numbers: \n");
        scanf("%d %d", &arr[0], &arr[1]);
        
        pthread_t tid;
        pthread_attr_t attr;
        
        pthread_attr_init(&attr);                         //default attributes
        pthread_create(&tid, &attr, add, (void *)arr); 
        pthread_join(tid, NULL);
        
        printf("sum = %d\n", sum);
}



