#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#define BUF_SIZE 1024
#define OPSZ 4
int calculate(int opnum, int opnds[], char operator);
int main(int argc, char *argv[]){
    int result;
    char data[BUF_SIZE];
    int opnd_cnt;
    // 创建套接字
    int server_socket = socket(PF_INET, SOCK_STREAM, 0);

    // 绑定地址和端口
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_family = AF_INET;

    int ret = bind(server_socket, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1){
        perror("bind");
        exit(1);
    }

    // 监听连接
    ret = listen(server_socket, 5);
    if(ret == -1){
        perror("listen");
        exit(2);
    }
    int client_socket;
    struct sockaddr_in caddr;
    socklen_t clnt_len = sizeof(caddr);
    int recv_len = 0;
    // 接受连接
    while(1){
        client_socket = accept(server_socket, (struct sockaddr *)&caddr, &clnt_len);
        if(client_socket == -1){
            perror("accept");
            exit(3);
        }
        // 接受一个有多少个操作数
        read(client_socket, &opnd_cnt, 1);

        // 接受数据
        while(recv_len < (opnd_cnt * OPSZ + 1)){
            int len = read(client_socket, &data[recv_len], BUF_SIZE - 1);
            recv_len += len;
        }
        result = calculate(opnd_cnt, (int *)data, data[recv_len - 1]);
        write(client_socket, (char *)&result, sizeof (result));
        close(client_socket);
    }

    close(server_socket);
    return 0;
}


int calculate(int opnum, int opnds[], char op){
    int result = opnds[0], i;
    switch(op){
        case '+':
            for(i = 1; i < opnum; i++) result += opnds[i];
            break;
        case '-':
            for(i = 1; i < opnum; i++) result -= opnds[i];
            break;
        case '*':
            for(i = 1; i < opnum; i++) result *= opnds[i];
            break;
        case '/':
            for(i = 1; i < opnum; i++) result *= opnds[i];
    }

    return result;
}
