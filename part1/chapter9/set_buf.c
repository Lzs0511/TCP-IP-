#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>


int main(int argc, char *argv[]){
    int sock, snd_buf, rcv_buf;
    socklen_t optlen;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket");
        exit(1);
    }
    snd_buf = 3 * 1024, rcv_buf = 3 * 1024;
    int state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, 
            (void *)&snd_buf, sizeof snd_buf);
    if(state){
        perror("setsockopt");
        exit(2);
    }
    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, 
            (void *)&rcv_buf, sizeof rcv_buf);
    if(state){
        perror("setsockopt");
        exit(3);
    }


    
	optlen = sizeof(snd_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, 
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
