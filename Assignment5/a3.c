#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<sys/sem.h>

#define SIZE 20

// required for semctl
union semun {
    int val;
};

int *buf, *sum, *in, *out;
int semid;

void P(int sem_num){                          // wait (P)
    struct sembuf op = {sem_num, -1, 0};
    semop(semid, &op, 1);
}

void V(int sem_num){                          // signal (V)
    struct sembuf op = {sem_num, 1, 0};
    semop(semid, &op, 1);
}

void producer(){
    for(int i = 1; i <= 100; i++){

        P(1); // empty--
        P(0); // mutex

        buf[*in] = i;
        *in = (*in + 1) % SIZE;

        V(0); // mutex
        V(2); // full++
    }
    exit(0);
}

void consumer(){
    while(1){

        P(2); // full--
        P(0); // mutex

        int item = buf[*out];
        *out = (*out + 1) % SIZE;

        V(0); // mutex
        V(1); // empty++

        if(item == -1)
            break;

        *sum += item;
    }
    exit(0);
}

int main(){

    int shmid[4];

    //shared buffer
    shmid[0] = shmget(IPC_PRIVATE, SIZE*sizeof(int), IPC_CREAT | 0666);
    buf = (int*) shmat(shmid[0], NULL, 0);

    //sum
    shmid[1] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    sum = (int*) shmat(shmid[1], NULL, 0);
    *sum = 0;

    //in index
    shmid[2] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    in = (int*) shmat(shmid[2], NULL, 0);
    *in = 0;

    //out index
    shmid[3] = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    out = (int*) shmat(shmid[3], NULL, 0);
    *out = 0;

    semid = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);               //semaphores: 0=mutex, 1=empty, 2=full

    union semun arg;

    arg.val = 1;
    semctl(semid, 0, SETVAL, arg); // mutex

    arg.val = SIZE;
    semctl(semid, 1, SETVAL, arg); // empty

    arg.val = 0;
    semctl(semid, 2, SETVAL, arg); // full

    int m, n;
    printf("Enter producers: ");
    scanf("%d", &m);
    printf("Enter consumers: ");
    scanf("%d", &n);

    pid_t pid;

    for(int i = 0; i < m; i++){
        if((pid = fork()) == 0){
            producer();
        }
    }

    for(int i = 0; i < n; i++){
        if((pid = fork()) == 0){
            consumer();
        }
    }

    for(int i = 0; i < m; i++)
        wait(NULL);

    for(int i = 0; i < n; i++){

        P(1); // empty
        P(0); // mutex

        buf[*in] = -1;
        *in = (*in + 1) % SIZE;

        V(0);
        V(2); // full
    }

    for(int i = 0; i < n; i++)
        wait(NULL);

    printf("\nFinal SUM = %d\n", *sum);

    shmdt(buf); shmdt(sum); shmdt(in); shmdt(out);

    for(int i = 0; i < 4; i++)
        shmctl(shmid[i], IPC_RMID, NULL);

    semctl(semid, 0, IPC_RMID);

    return 0;
}
