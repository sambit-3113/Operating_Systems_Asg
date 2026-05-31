#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<sys/sem.h>

// union required for semctl
union semun {
    int val;
};

int main(){
    pid_t c, d;

    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    int *x = (int *) shmat(shmid, NULL, 0);
    *x = 0;

    //Semaphore creation (1 semaphore)
    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);

    union semun arg;
    arg.val = 1;  // initialize to 1 (mutex)
    semctl(semid, 0, SETVAL, arg);

    //Defined wait (P) and signal (V)
    struct sembuf wait_op = {0, -1, 0};   // decrement
    struct sembuf signal_op = {0, 1, 0};  // increment

    c = fork();

    if (c != 0){
        d = fork();
    }
    
    //C1
    if (c == 0){
        for (int i = 0; i < 10; i++){

            semop(semid, &wait_op, 1);  //LOCK

            int temp = *x;
            temp = temp + 2;
            *x = temp;
            printf("C1 updated x = %d\n", *x);

            semop(semid, &signal_op, 1); //UNLOCK

            sleep(1);
        }
        exit(0);
    }

    //C2
    else if (c != 0 && d == 0){
        for (int i = 0; i < 10; i++){

            semop(semid, &wait_op, 1);   //LOCK

            int temp = *x;
            temp = temp - 2;
            *x = temp;
            printf("C2 updated x = %d\n", *x);

            semop(semid, &signal_op, 1); //UNLOCK

            sleep(1);
        }
        exit(0);
    }

    //Parent
    else{
        wait(NULL);
        wait(NULL);

        printf("Final x: %d\n", *x);

        shmdt(x);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);  // delete semaphore
    }

    return 0;
}
