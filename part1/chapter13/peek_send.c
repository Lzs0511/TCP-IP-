#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_family = AF_INET;
    

    if(connect(sock, (struct sockaddr *)&saddr, sizeof saddr) == -1){
        perror("connect");
        exit(2);
    }

    write(sock, "123", strlen("123"));
    close(sock);
    return 0;
}