#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in servaddr;
    char message[30];
    int str_len = 0;
    int idx = 0, read_len = 0;

    if(argc != 3){
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket() error!");
        exit(2);
    }

    memset(&servaddr, 0, sizeof servaddr);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_family = AF_INET;

    if(connect(sock, (struct sockaddr *)&servaddr, (socklen_t)sizeof(servaddr)) == -1){
        perror("socket() error!");
        exit(3);
    }

    while(read_len = read(sock, message + idx++, 1)){
        if(read_len == -1){
            perror("read() error!");
            exit(4);
        }
        str_len += read_len;
    }
    printf("Message from server: %s\n", message);
    printf("Function read call count: %d\n", str_len);
    close(sock);
    return 0;

}