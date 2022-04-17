#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
void error_handling(char *message);

int main(int argc, char *argv[]){
    int fd;
    char buf[] = "Let's go! \n";
    fd = open("data.txt", O_CREAT | O_WRONLY);
    if(fd == -1)
        error_handling("open() error!");
    
    printf("file descriptor: %d \n", fd);

    if(write(fd, buf, sizeof(buf)) == -1){
        error_handling("write() error!");
    }
    close(fd);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
