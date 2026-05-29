#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/mman.h>

int main(){
	const int SIZE = 4096;
	const char *name = "SM1";
	int shm_fd;
	void *ptr;
	shm_fd = shm_open(name, O_RDONLY, 0666);
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	
	int *a = (int*)ptr;
	ptr += sizeof(*a);

	char* b = (char *)ptr;
	printf("The word consumed is:\n");
	printf("%s", b);

	if (*a%2 != 0){
	printf("%d is odd.\n", *a);
	}
	else{
	printf("%d is even.\n", *a);
	}
	
	shm_unlink(name);
	return 0;
}


