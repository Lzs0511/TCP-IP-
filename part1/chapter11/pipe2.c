#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define BUF_SIZE 30
int main()
{
    int fds[2];
    char str1[] = "Who are you?";
    char str2[] = "Thank you for your message";
    char buf[BUF_SIZE];
    pipe(fds);
    pid_t pid = fork();
    if(pid == 0)
    {
        write(fds[1], str1, sizeof str1);
        // sleep(2);
        read(fds[0], buf, BUF_SIZE);
        printf("Child proc output: %s \n", buf);
    }
    else
    {
        read(fds[0], buf, sizeof buf);
        printf("Parent proc output: %s \n", buf);
        write(fds[1], str2, sizeof str2);
        sleep(3);
    }
    return 0;   
}