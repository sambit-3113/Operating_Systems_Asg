#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <time.h>

int main(){
	const int SIZE = 4096;
	const char *name = "SM2";
	
	int shm_fd;
	int *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR,  0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	srand(time(NULL));			// just to avoid the same seed

	for(int i = 0; i < 100; i++){
		ptr[i] = rand() % 1000;		//ptr[i] is value stored at i (i.e it means *(ptr+i) = the number)
		//printf("%d\n", ptr[i]);
	}

	printf("100 random numbers written to shared memory.\n");

	return 0;
}
