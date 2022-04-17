#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
    int status;
    pid_t pid = fork();
    if(pid == 0){
        puts("This is child process！");
        exit(3);
    }else{
        printf("Child PID: %d\n", pid);
        pid = fork();
        if(pid == 0){
            exit(7);
        }else{
            printf("Child PID: %d \n", pid);
            wait(&status);
            if(WIFEXITED(status))
                printf("Child send one: %d\n", WEXITSTATUS(status));

            wait(&status);
            if(WIFEXITED(status)){
                printf("Child send two: %d\n", WEXITSTATUS(status));
            }

            sleep(30);
        }
    }
    return 0;
}