#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define BUF_SIZE 30
int main(int argc, char *argv[]){
    int fds[2];
    char str[] = "Who are you";
    char buf[BUF_SIZE];
    pipe(fds);
    pid_t pid = fork();
    if(pid == 0){
        // 父进程
        write(fds[1], str, sizeof str);
    }else{
        read(fds[0], buf, sizeof buf);
        printf("Accept from parent process: %s\n", buf);
    }
    return 0;
}