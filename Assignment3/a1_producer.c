#include<stdio.h>			//for printf(), scanf()
#include<stdlib.h>			//for memory management (general utility)
#include<string.h>			//string manipulation func. (like strlen())
#include<fcntl.h>			//for O_CREAT, O_RDWR, etc.
#include<sys/shm.h>			//for shared memory operations
#include<sys/stat.h>			//file permission constants(like 0666, etc.)
#include<sys/mman.h>			//for PROT_WRITE
#include<unistd.h>			//for ftruncate

int main(){
	const int SIZE = 4096;
	const char *name = "SM1";
	

	int num;
	printf("Enter a num:\n");
	scanf("%d", &num);

	char *word = malloc(100 * sizeof(char));    // scanf store str in random mem -> prog may crash.
	printf("Enter a string:\n");
	scanf("%s", word);

	int shm_fd;

	void *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	/* store integer */
    	*((int*)ptr) = num;
    	ptr += sizeof(int);

	sprintf(ptr, "%s\n", word);
	ptr += strlen(word);

	return 0;
}
