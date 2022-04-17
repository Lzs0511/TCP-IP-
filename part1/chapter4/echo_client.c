#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUFSIZE 30
int main(int argc, char *argv[]){
    char message[BUFSIZE];
    if(argc != 3){
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    // 定义客户端的套接字
    int client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        perror("socket");
        exit(2);
    }


    // 连接服务器
    // 1. 定义服务器的地址信息
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof server_addr);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_family = AF_INET;

    // 2. 使用 connect连接服务器
    int is_success = connect(client_socket, (struct sockaddr *)&server_addr, sizeof server_addr);
    if(is_success == -1){
        perror("connect");
        exit(3);
    }


    // 3. 进行通信
    int len = 0;
    while(1){

        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUFSIZE ,stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")){
            break;
        }
        int write_len = write(client_socket, message, BUFSIZE - 1);
        int recv_len = 0;
        while(recv_len < write_len){
        len = read(client_socket, &message[recv_len], BUFSIZE);
        if(len > 0){
            recv_len += len;
        }else if(len == -1){
            perror("read");
            exit(4);
        }
        }
        printf("Receive the infomation of server: %s", message);
    }
    close(client_socket);
    return 0;

}