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
    
    if(argc != 2){
        printf("Usage: %s <port>", argv[0]);
        exit(1);
    }
    char message[30];
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        myerror("socket", 2);
    }
    // 绑定地址和端口
    struct sockaddr_in saddr, caddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = INADDR_ANY;
    
    int ret = bind(sock, (struct sockaddr *)&saddr, sizeof saddr);
    if(ret){
        myerror("bind", 2);
    }
    socklen_t clnt_size = 0;
    for(int i = 0; i < 3; i++){
         //sleep(5);
        ssize_t recv_len = recvfrom(sock, message, sizeof message, 0, (struct sockaddr *)&caddr, &clnt_size);
        printf("receive message %d: %s", i+1, message);
    }
    close(sock);
    return 0;
}
