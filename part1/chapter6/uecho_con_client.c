#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

    // 创建套接字
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        perror("socket");
        exit(2);
    }

    // 注册目标服务器的地址和端口，并创建已连接套接字
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &saddr.sin_addr);
    //saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_family = AF_INET;
    int ret = connect(sock, (struct sockaddr *)&saddr, sizeof saddr);
    if(ret == -1){
        perror("connect");
        exit(3);
    }

    const int BUF_SIZE = 30;
    char message[BUF_SIZE];
    // 发送信息
    while(1){
        fputs("please input infomation to server:", stdout);
        fgets(message, sizeof message, stdin);
        printf("message: %s\n", message);
        send(sock, message, strlen(message) + 1, 0);
        //  write(sock, message, strlen(message) + 1);
    }
    close(sock);
    return 0;
}
