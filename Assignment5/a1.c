#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>

int main(){
        pid_t c, d;
        
        int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);     //IPC_Private (only processes related to fork can utilize this)
        int *x = (int *) shmat(shmid, NULL, 0);                             //Without this, we cannot access shared memory.
        *x = 0;
        
        c = fork();
        
        if (c != 0){
                d = fork();
        }
        
        if (c == 0){
                for (int i = 0; i < 10; i++){
                        int temp = *x;
                        temp = temp + 2;
                        *x = temp;
                        printf("C1 updated x = %d\n", *x);
                        sleep(1);                                     // sleep between ith write and (i+1)th read
                }
        }
        
        else if (c != 0 && d == 0){
                 for (int i = 0; i < 10; i++){
                        int temp = *x;
                        sleep(1);                                     // sleep between ith read and (i+1)th write
                        temp = temp - 2;
                        *x = temp;
                        printf("C2 updated x = %d\n", *x);
                }
        }
        
        else{
                wait(NULL);
                wait(NULL);
                printf("Final x: %d\n", *x);
                
                shmdt(x);
                shmctl(shmid, IPC_RMID, NULL);
        }
        
        return 0;
}
