#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#define MAXSIZE 30
int main(int argc, char *argv[]){
    char message[MAXSIZE];
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        perror("socket");
        exit(1);
    }
    // 绑定ip地址和端口号
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof server_addr);
    // server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_family = AF_INET;
    bind(server_socket, (struct sockaddr*) &server_addr, sizeof server_addr);
    // 等待连接请求
    // int clnt_socket;
    // clnt_socket = ;
    if(listen(server_socket, 5) == -1){
        perror("listen");
        exit(2);
    }
    // 定义客户端的 sockaddr_in 
    struct sockaddr_in clnt_addr;
    socklen_t clnt_len = sizeof(clnt_addr);
    
    for(int i = 0; i != 5; i++){
        printf("i: %d\n", i);
        // 与客户端通信
        int clnt_sock = accept(server_socket, (struct sockaddr *)&clnt_addr, &clnt_len);
        if(clnt_sock == -1){
            perror("accept");
            exit(3);
        }
        printf("Connected client %d \n", i + 1);
        int len = 0;
        while((len = read(clnt_sock, message, MAXSIZE)) != 0){
            printf("the len of read file: %d\n", len);
            printf("the content is : %s\n", message);
            write(clnt_sock, message, len);
        }
        close(clnt_sock);
    }

    close(server_socket);
    return 0;
    
}