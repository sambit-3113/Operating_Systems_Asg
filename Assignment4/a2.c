#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int fd;

//Thread 1 create file.
void *create_file(void *arg){
        fd = open("data.txt", O_CREAT | O_WRONLY, 0644);
        
        if (fd >=0) {
                printf("file created successfully.\n");
        }
        else{
                perror("file creation failed.");
        }
        
        pthread_exit(NULL);
}

//Thread 2 write content to it.
void *write_content(void *arg){
        char data[100];
        
        printf("Enter text to write:");
        fgets(data, sizeof(data), stdin);
        
        write(fd, data, strlen(data));
        close(fd);
        
        pthread_exit(NULL);      
        }


int main(){
        pthread_t t1, t2;
        
        // Create thread T1
        pthread_create(&t1, NULL, create_file, NULL);       //NULL when default attributes.
        pthread_join(t1, NULL);   // ensure file is created first

        // Create thread T2
        pthread_create(&t2, NULL, write_content, NULL);
        pthread_join(t2, NULL);

        return 0;
}
