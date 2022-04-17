#include<netinet/tcp.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
// #include<sys/types.h>
#define TRUE 1
#define FALSE 0
int main(int argc, char *argv[]){
    int sock;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket");
        exit(1);
    }

    // 创建服务器地址信息
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = INADDR_ANY;
    // 绑定端口
    int state = bind(sock, (struct sockaddr *)&saddr, sizeof saddr);
    if(state == -1){
        perror("bind");
        exit(2);
    }
    
    // 监听
    state = listen(sock, 5);
    if(state == -1){
        perror("listen");
        exit(3);
    }

    int optval = 0;
    socklen_t optlen = sizeof optval;
    state = getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, 
            (void *)&optval, &optlen);
    if(state == -1){
        perror("getsockopt");
        exit(4);
    }
    printf("nagle is %d\n", optval);
     
    optval = TRUE;
    // 禁用nagle 算法
    state = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, 
            (void *)&optval, optlen);
    if(state == -1){
        perror("getsockopt");
        exit(5);
    }
    printf("modify nagle, now the nagle variety is %d\n", optval);
    optval = FALSE;
    state = getsockopt(sock, IPPROTO_TCP, TCP_NODELAY, 
            (void *)&optval, &optlen);
    if(state == -1){
        perror("getsockopt");
        exit(4);
    }
    printf("nagle is %d\n", optval);

    return 0;
}
