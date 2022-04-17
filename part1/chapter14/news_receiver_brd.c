#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define BUF_SIZE 30
int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Usage : %s <GroupIP> <Port>\n", argv[0]);
        exit(1);
    }
    printf("1\n");
    char buf[BUF_SIZE];
    struct sockaddr_in adr;
    memset(&adr, 0, sizeof adr);
    adr.sin_addr.s_addr = INADDR_ANY;
    adr.sin_port = htons(atoi(argv[1]));
    adr.sin_family = AF_INET;

    printf("1\n");
    int recv_sock = socket(PF_INET, SOCK_DGRAM, 0);

    if(bind(recv_sock, (struct sockaddr *)&adr, sizeof adr) == -1){
        perror("bind");
        exit(2);
    }

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