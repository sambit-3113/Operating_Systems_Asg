#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

void *array_op(void *arg){
        int *arr = (int *)arg;
        for (int i = 0; i < 10000; i++){
                printf("a[%d] = %d \n", i, (arr[i] + 2) * 4);
        }
        return NULL;
}


int main(){ 
        pthread_t t1, t2;
        int array[10000];
        
        srand(time(NULL));
        for (int i = 0; i < 10000; i++){
                array[i] = rand() % 1000;
        }
        printf("Threads starting...\n");
        pthread_create(&t1, NULL, array_op, (void *)array);
        pthread_create(&t2, NULL, array_op, (void *)array);
        sleep(1);
        pthread_cancel(t1);
        pthread_cancel(t2);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        printf("Threads ending...\n");
        
        return 0;
}

