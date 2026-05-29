#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/mman.h>

int main(){
	const int SIZE = 4096;
	const char *name = "SM2";

	int shm_fd;
	int *ptr;
	int sum = 0;


	shm_fd = shm_open(name, O_RDONLY, 0666);
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

	for (int i = 0; i < 100; i++){
		sum += ptr[i];
	}

	printf("Sum = %d\n", sum);

	shm_unlink(name);

	return 0;
}
