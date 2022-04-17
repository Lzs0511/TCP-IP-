#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[]){

    if(argc != 2){
        fprintf(stdout, "Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof saddr);
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_family = AF_INET;
    bind(sock, (struct sockaddr *)&saddr, sizeof saddr);
    listen(sock, 5);
    struct sockaddr_in clnt_addr;
    socklen_t clnt_sz;
    int clnt_sock = accept(sock, (struct sockaddr *)&clnt_addr, &clnt_sz);

    FILE* writefp = fdopen(clnt_sock, "w");
    FILE *readfp = fdopen(clnt_sock, "r");
    fputs("From Server: Hi ~ client? \n", writefp);
    fputs("I love all of the world \n", writefp);
    fputs("You are awesome! \n", writefp);
    fflush(writefp);
    fclose(writefp);
    char buf[30] = {0};
    fgets(buf, 30, readfp);
    fputs(buf, stdout);
    fclose(readfp);
    return 0;
}