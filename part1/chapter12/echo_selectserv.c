#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/select.h>
#include<arpa/inet.h>
#include<sys/time.h>
#define BUF_SIZE 128

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    char buf[BUF_SIZE];
    // 1. 创建服务器端和客户端套接字变量
    struct timeval timeout;
    int serv_sock = socket(PF_INET, SOCK_STREAM, 0), clnt_sock;
    if(serv_sock == -1){
        perror("socket");
        exit(1);
    }
    // 2. 创建客户端和服务器端地址信息变量
    struct sockaddr_in saddr, clnt_addr;
    socklen_t clnt_sz;
    // 3. 初始化地址信息变量和绑定套接字
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr *)&saddr, sizeof saddr) == -1){
        perror("bind");
        exit(2);
    }
    // 4. 监听
    if(listen(serv_sock, 5) == -1){
        perror("listen");
        exit(3);
    }
    // 5. 设置文件描述符集合，并将服务器端套接字加进去
    fd_set reads, cpy_reads;
    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    int maxfd = serv_sock;
    /*
         6. 无限循环接受数据
            1. 拷贝一份文件描述符集合
            2. 循环遍历每个文件描述，判断文件描述符是否有变化
                1. 如果服务器套接字有变化，则有新连接进来，将客户端套接字加入到文件描述符集合中
                2. 如果客户端套接字有变化，则接受数据
    */
   while(1){
        cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        int change = select(maxfd + 1, &cpy_reads, 0, 0, &timeout);
        if(change == -1) break;
        else if(change == 0){
            puts("timeout...\n");
            continue;
        }else{
            for(int i = 0; i < maxfd + 1; i++){
                if(FD_ISSET(i, &cpy_reads)){
                    if(i == serv_sock){
                        // 有新连接进来
                        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_sz);
                        if(clnt_sock == -1){
                            perror("accept");
                            exit(5);
                        }else{
                            FD_SET(clnt_sock, &reads);
                            if(clnt_sock > maxfd) {
                                maxfd = clnt_sock;
                            }
                            printf("connected client : %d \n", clnt_sock);
                        }
                    }else {
                        int len = read(i, buf, BUF_SIZE);
                        if(len == 0){
                            // 客户端已断开
                            printf("client %d closed...\n", i);
                            FD_CLR(i, &reads);
                            close(i);
                        }else if(len == -1){
                            perror("read");
                            exit(6);
                        }else {
                            write(i, buf, len);
                        }
                    }
                }
            }
        }
   }
    close(serv_sock);
    return 0;

}