#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    int fds1[2], fds2[2];
    int ret = pipe(fds1);
    if(ret == -1)
    {
        perror("pipe");
        exit(1);
    }
    ret = pipe(fds2);
    if(ret == -1)
    {
        perror("pipe");
        exit(2);
    }

    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message!";
    char buf[BUF_SIZE];

    pid_t pid = fork();
    if(pid == 0)
    {
        write(fds1[1], str1, sizeof str1);
        read(fds2[0], buf, sizeof buf);
        printf("Parent proc recv: %s \n", buf);
    }
    else
    {
        read(fds1[0], buf, sizeof buf);
        write(fds2[1], str2, sizeof str2);
        printf("Child proc recv: %s \n", buf);
        sleep(2);
    }
    return 0;
}