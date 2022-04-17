#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#define BUF_SIZE 30
void readinfo(int sock, char *message);
void writeinfo(int sock, char *message);
int main(int argc, char *argv[])
{
    char message[BUF_SIZE];
    pid_t pid;
    if(argc != 3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {   
        perror("socket");
        exit(1);
    }

    // 创建服务器端信息，并连接服务器
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    

    if(connect(sock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
    {
        perror("connect");
        exit(2);
    }
    memset(message, 0, sizeof message);
    pid = fork();
    if(pid == 0)
    {
        readinfo(sock, message);
    }
    else if(pid > 0)
    {   
        writeinfo(sock, message);
    }
    close(sock);
    return 0;
}

void readinfo(int sock, char *message)
{
    int rd_len;
    while((rd_len = read(sock, message, BUF_SIZE)) > 0)
    {
        printf("Receive from Server: %s", message);
    }

}

void writeinfo(int sock, char *message)
{
    while(1)
    {
        fputs("Please Input some words: ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        {
            shutdown(sock, SHUT_WR);
            return ;
        }
        write(sock, message, strlen(message));
    }
}
