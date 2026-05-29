#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/mman.h>

int fact(int n){
        if (n == 0 || n == 1){
                return 1;
        }
        
        else{
                return n * fact(n-1);
        }
}

int main(){
        const int SIZE = 4096;
	const char *name = "SM3";
	int shm_fd;
	int *ptr;
	shm_fd = shm_open(name, O_RDONLY, 0666);
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	
	for (int i = 0; i < 4; i++){
	        printf("Factorial of %d is %d \n", ptr[i], fact(ptr[i]));
	}
	return 0;
}
