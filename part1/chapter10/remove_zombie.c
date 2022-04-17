#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void handler_sigchld(int sig);
int main(int argc, char *argv[])
{
    // 注册信号捕捉
    struct sigaction sigact;
    sigact.sa_handler = handler_sigchld;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigaction(SIGCHLD, &sigact, 0);

    // 创建三个子进程
	pid_t pid;
    for(int i = 0; i < 3; i++)
    {
       	pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    if(pid == 0)
    {
        printf("child %d created...\n", getpid());
        sleep(3);
        return 3;
    }
    else
    {
        for(int i = 0; i < 20; i++)
        {
            sleep(20);
        }
    }
    return 0;
}
void handler_sigchld(int sig)
{
    int status;
    int child_pid;
    if(sig == SIGCHLD)
    {
        /**
        while(!waitpid(-1, &status, WNOHANG))
        {
            
        }
        
        child_pit = waitpid(-1, &status, WNOHANG);
        if(!child_pid)
        if(WIFEXITED(status)
        */
        puts("have one or more SIGCHLD signals were caught...");
        /**
   		while(!waitpid(-1, &status, WNOHANG))
        {   
            puts("sleep 3sec.");
            sleep(3);
        }   

        if(WIFEXITED(status))
        {   
            printf("Child send %d \n", WEXITSTATUS(status));
        }   
        */
        child_pid = waitpid(-1, &status, WNOHANG);
        if(WIFEXITED(status))
        {
            printf("Removed proc id: %d\n", child_pid);
            printf("Child send: %d \n", WEXITSTATUS(status));
        }
    }
}
