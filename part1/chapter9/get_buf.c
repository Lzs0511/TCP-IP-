#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]){
    int sock;
    int snd_buf, rcv_buf;
    int optlen;

    // 创建套接字
    sock = socket(PF_INET, SOCK_STREAM, 0);

    // 获取输出缓冲区的大小
    optlen = sizeof(snd_buf);
    int state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, 
            (void *)&snd_buf, &optlen);

    if(state){
        perror("getsockopt");
        exit(1);
    }
    printf("snd_buf size is %d\n", snd_buf);

    // 获取输入缓冲区大小
    optlen = sizeof(rcv_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF,
            (void *)&rcv_buf, &optlen);

    if(state){
        perror("getsockopt");
        exit(1);
    }
    printf("rcv_buf size is %d\n", rcv_buf);
    return 0;
}
