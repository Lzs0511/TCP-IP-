#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#define BUF_SIZE 100
void read_childproc(int sig);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage %s <port> \n", argv[0]);
        exit(1);
    }
    int serv_sock, clnt_sock;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    int fds[2];
    struct sockaddr_in saddr, caddr;
    pid_t pid;
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];
    struct sigaction act;

    // 注册信号
    act.sa_handler = read_childproc;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    
    state = sigaction(SIGCHLD, &act, 0);

    // 保存服务器地址信息
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_family = AF_INET;

    // 绑定套接字
    if(bind(serv_sock, (struct sockaddr *)&saddr, sizeof saddr) == -1)
    {
        perror("bind");
        exit(3);
    }
    
    // 监听
    if(listen(serv_sock, 5) == -1)
    {
        perror("listen");
        exit(4);
    }

    pipe(fds);
    pid = fork();

    if(pid == 0)
    {
        // 子进程处理写文件
        FILE *fp = fopen("echomsg.txt", "wt");
        char msgbuf[BUF_SIZE];
        int len;
        for(int i = 0; i < 10; i++)
        {
            len = read(fds[0], msgbuf, BUF_SIZE);
            fwrite((void *)msgbuf, 1, len, fp);
        }
        printf("child process has finished writing\n");
        fclose(fp);
        return 0;
    }

    while(1)
    {
        adr_sz = sizeof(caddr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&caddr, &adr_sz);
        if(clnt_sock == -1)
        {
            continue;
        }
        else
            puts("New client connected...\n");

        pid = fork();
        if(pid == 0)
        {
            close(serv_sock);
            while((str_len = read(clnt_sock, buf, sizeof buf)) != 0)
            {
                write(clnt_sock, buf, str_len);
                write(fds[1], buf, str_len);
            }
            close(clnt_sock);
            puts("client disconnected...\n");
            return 0;
        }
        else
            close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}


void read_childproc(int sig)
{
    int status;

    if(sig == SIGCHLD)
    {
        pid_t pid = waitpid(-1, &status, WNOHANG);
        if(WIFEXITED(status))
        {
            printf("Removed proc id: %d \n", pid);
            printf("Child send: %d \n", WEXITSTATUS(status));
        }
    }
}