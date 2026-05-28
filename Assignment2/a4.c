#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

	pid_t p0, p1, p2;
	p0 = getpid();
	p1 = fork();
	p2 = fork();

	if(p1 > 0 && p2 > 0){
		printf("P:\n");
		printf("Hi! I am a root process.\n");
		printf("My PID is %d\n", getpid());
		wait(NULL);
	}

	else if (p1 == 0 && p2 > 0){
		printf("R:\n");
		printf("Hi! I am a child process R of Parent P.\n");
		printf("My PID is %d\n", getpid());
		printf("MY Parent PID is %d\n", getppid());
		wait(NULL);
	}

	else if (p1 == 0 && p2 == 0){
		printf("U:\n");
		printf("Hi! I am a child process U of Parent R.\n");
		printf("My PID is %d.\n", getpid());
		printf("MY Parent PID is %d.\n", getppid());
		printf("My Grand Parent PID is %d.\n",p0);
	}

	else{
		pid_t p3, p4;
		p3 = fork();
		if (p3 == 0){
			printf("S:\n");
			printf("Hi! I am a child process S of Parent Q.\n");
			printf("My PID is %d.\n",getpid());
			printf("MY Parent PID is %d.\n", getppid());
			printf("My Grand Parent PID is %d.\n",p0 );
		}

		else{
			p4 = fork();
			if (p4 == 0){
				printf("T:\n");
				printf("Hi! I am a child process T of Parent Q.\n");
				printf("My PID is %d.\n", getpid());
				printf("MY Parent PID is %d.\n", getppid());
				printf("My Grand Parent PID is %d.\n", p0);
			}
			
			else{
			        printf("Q:\n");
		                printf("Hi! I am a child process Q of Parent P.\n");
		                printf("My PID is %d\n", getpid());
		                printf("MY Parent PID is %d\n", getppid());
		                wait(NULL);
			}
		}
	}

}
