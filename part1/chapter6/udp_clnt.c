#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 30


int main(int argc, char *argv[]){

    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_sz;

    struct sockaddr_in saddr, fromaddr;
    if(argc != 3){
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        perror("socket");exit(2);
    }

    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));

    while(1){
        fputs("Insert message (q to quit): ", stdout);

        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")){
            break;
        }

        sendto(sock, message, strlen(message), 0, (struct sockaddr *)&saddr, sizeof saddr);
        adr_sz = sizeof(fromaddr);
        str_len = recvfrom(sock, message, sizeof message, 0, (struct sockaddr *)&fromaddr, &adr_sz);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }

    close(sock);
    return 0;
}