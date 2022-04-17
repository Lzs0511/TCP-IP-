#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/socket.h>
#include<sys/wait.h>
#define BUF_SIZE 30
void read_childproc(int sig);
int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;

    char buf[BUF_SIZE];
    if(argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof serv_addr);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(serv_sock, (struct sockaddr *)& serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(2);
    }

    if(listen(serv_sock, 5) == -1)
    {
        perror("listen");
        exit(3);
    }

    while(1)
    {
        adr_sz = sizeof clnt_addr;
        clnt_sock = accept(serv_sock, (struct sockaddr *)& clnt_addr, &adr_sz);
        if(clnt_sock == -1)
            continue;
        else
        {
            puts("New Client Connected...");
        }

        pid = fork();
        if(pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        if(pid == 0)
        {
            close(serv_sock);
            while((str_len = read(clnt_sock, buf, sizeof buf)) > 0)
            {
                write(clnt_sock, buf, str_len);
            }

            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }else
        {
            close(clnt_sock);
        }
    }
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("remove proc id: %d\n", pid);
}