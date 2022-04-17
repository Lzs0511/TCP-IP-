#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;
    optlen = sizeof sock_type;
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
    printf("SOCK_STREAM: %d \n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d \n", SOCK_DGRAM);

    state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, 
            (void *)&sock_type, &optlen);
    if(state){
        perror("getsockopt");
        exit(1);
    }

    printf("Socket type one: %d \n", sock_type);

    state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE,
            (void *)&sock_type, &optlen);
    
    if(state){
        perror("getsockopt");
        exit(1);
    }
    printf("Socket type two: %d \n", sock_type);

    return 0;
}
