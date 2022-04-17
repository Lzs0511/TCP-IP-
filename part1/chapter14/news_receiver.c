#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define BUF_SIZE 30
int main(int argc, char *argv[]){

    if(argc != 3){
        printf("Usage : %s <GroupIP> <Port>\n", argv[0]);
        exit(1);
    }
    printf("1\n");
    char buf[BUF_SIZE];
    struct sockaddr_in adr;
    struct ip_mreq join_adr;
    memset(&adr, 0, sizeof adr);
    adr.sin_addr.s_addr = INADDR_ANY;
    adr.sin_port = htons(atoi(argv[2]));
    adr.sin_family = AF_INET;

    printf("1\n");
    int recv_sock = socket(PF_INET, SOCK_DGRAM, 0);

    if(bind(recv_sock, (struct sockaddr *)&adr, sizeof adr) == -1){
        perror("bind");
        exit(2);
    }
    printf("1\n");
    join_adr.imr_multiaddr.s_addr = inet_addr(argv[1]);
    join_adr.imr_interface.s_addr = INADDR_ANY;

    setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&join_adr, sizeof join_adr);
    printf("1\n");
    while(1){
        int len = recvfrom(recv_sock, buf, BUF_SIZE - 1, 0, NULL, 0);
        if(len < 0)
        {
            perror("recvfrom");
            break;
        }
        buf[len] = 0;
        fputs(buf, stdout);
    }
    close(recv_sock);
    return 0;
}