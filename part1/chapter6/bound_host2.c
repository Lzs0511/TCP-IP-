#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
void myerror(const char *msg, int errno){
    perror(msg);
    exit(errno);
}


int main(int argc, char *argv[]){
    // 创建套接字
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        myerror("socket", 1);
    }
    
    // 绑定服务器的地址和端口信息
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_family = AF_INET;

    char *msg1 = "Hello UDP Server!\n";
    char *msg2 = "I am a UDP Client!\n";
    char *msg3 = "How do you do?\n";
    // 向服务器发送信息
    printf("send msg1\n");
    sendto(sock, msg1, strlen(msg1)+1, 0, (struct sockaddr *)&saddr, sizeof saddr);
    
    printf("send msg2\n");
    sendto(sock, msg2, strlen(msg2)+1, 0, (struct sockaddr *)&saddr, sizeof saddr);

    printf("send msg3\n");
    sendto(sock, msg3, strlen(msg3)+1, 0, (struct sockaddr *)&saddr, sizeof saddr);

    return 0;
}

