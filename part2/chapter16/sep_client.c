#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char *argv[]){
    
    if(argc != 3){
        printf("Usage: %s <IP> <Port> \n", argv[0]);
        exit(1);
    }
    FILE *readfp, *writefp;

    int sock = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_family = AF_INET;

    connect(sock, (struct sockaddr *)&saddr, sizeof saddr);

    readfp = fdopen(sock, "r");
    writefp = fdopen(sock, "w");

    char buf[1024];
    while(1){
        if(fgets(buf, sizeof buf, readfp) == NULL)break;
        fputs(buf, stdout);
        fflush(stdout);
    }
    fputs("From Client: Thank you! \n", writefp);
    fflush(writefp);
    fclose(writefp);
    fclose(readfp);

    return 0;
}