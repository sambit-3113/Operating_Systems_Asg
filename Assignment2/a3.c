#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int fib(int n){
	if (n == 1){
		return 0;
	}

	else if (n == 2){
		return 1;
	}

	else{
		return fib(n-1)+fib(n-2);
	}
}


int fac(int n){
	if (n == 0 || n == 1){
		return 1;
	}

	else{
		return n * fac(n-1);
	}
}

int main(){	
	int n=0,m=0;
	scanf("%d",&m);
	scanf("%d",&n);
	pid_t v;
	v=fork();
	if (v == 0){
		printf("Hi! I am a child process.\n");
		printf("My PID is %d\n",getpid());
		printf("MY Parent PID is %d\n", getppid());
		printf("Fibonacci numbers for %d numbers:\n",m);
		for (int i = 1; i <= m-1; i++){
			printf("%d,",fib(i));
		}
		printf("%d.\n",fib(m));
	}

	else{
		//wait(NULL);
		printf("Hi! I am a parent process.\n");
		printf("My PID is %d\n", getpid());
		printf("Factorial for number %d: %d\n",n, fac(n));
		printf("I am terminated earlier than my child.\n");
	}

	return 0;
}
