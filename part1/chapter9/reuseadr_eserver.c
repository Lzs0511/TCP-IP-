#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]){

    int serv_sock, clnt_sock;
    char message[30];
    int option, str_len;
    socklen_t optlen, clnt_adr_size;
    struct sockaddr_in saddr, caddr;
    if(argc != 2){
        printf("Useage :%s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        perror("socket");
        exit(2);
    }

    optlen = sizeof(option);
    option = TRUE;

    int state = setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&option, optlen);
    
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(serv_sock, (struct sockaddr *)&saddr, sizeof saddr) == -1){
        perror("bind");
        exit(3);
    }

    if(listen(serv_sock, 5) == -1){
        perror("listen");
        exit(4);
    }

    clnt_adr_size = sizeof caddr;
    clnt_sock = accept(serv_sock, (struct sockaddr *)&caddr, &clnt_adr_size);
    if(clnt_sock == -1){
        perror("accept");
        exit(5);
    }

    while((str_len = read(clnt_sock, message, sizeof message)) != 0){
        write(clnt_sock, message, str_len);
        write(1, message, str_len);
    }

    close(clnt_sock);
    close(serv_sock);
    return 0;
}