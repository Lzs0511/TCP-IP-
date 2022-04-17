#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void timeout(int sig)
{
    if(sig == SIGALRM)
    {
        puts("Time out!!!");
        
    }
    alarm(2);
}
void keycontrol(int sig)
{
    if(sig == SIGINT)
        puts("CTRL + C Pressed");
}
int main(int argc, char *argv[])
{
    struct sigaction sigact;
    sigact.sa_handler = timeout;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    struct sigaction sigact1;

    sigact1.sa_handler = keycontrol;
    sigemptyset(&sigact1.sa_mask);
    sigact1.sa_flags = 0;
    sigaction(SIGALRM, &sigact, 0);
    sigaction(SIGINT, &sigact1, 0);
    alarm(2);

    for(int i = 0; i < 3; i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}
