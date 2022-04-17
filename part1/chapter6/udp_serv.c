#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 30
int main(int argc, char *argv[])
{
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;
    struct sockaddr_in saddr, caddr;

    if(argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);

    if(serv_sock == -1)
    {
        perror("socket");
        exit(1);
    }

    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_family = AF_INET;

    if(bind(serv_sock, (struct sockaddr *)&saddr, sizeof(saddr))){
        perror("bind");
        exit(2);
    }

    while(1){
        clnt_adr_sz = sizeof(caddr);
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr *)&caddr, &clnt_adr_sz);
        sendto(serv_sock, message, str_len, 0, (struct sockaddr *)&caddr, clnt_adr_sz);
    }

    close(serv_sock);
    return 0;
}