#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t v;
	v = fork();

	if (v == 0){
		printf("Hi! I am a child process.\n");
		printf("My PID is %d\n", getpid());
		printf("MY Parent PID is %d\n", getppid());
	}
	
	else{
		wait(NULL);
		printf("Hi! I am a Parent process.\n");
		printf("My PID is %d\n", getpid());
		printf("My Child PID is %d\n", v);
	}

	return 0;
}
