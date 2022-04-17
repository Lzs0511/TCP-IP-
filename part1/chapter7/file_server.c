#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 30
int main(int argc, char *argv[]){
    int serv_sd, clnt_sd;
    FILE *fp;
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_adr_sz;

    if(argc != 2){
        printf("Usage: %s <IP> <port>", argv[0]);
        exit(1);
    }

    fp = fopen("file_server.c", "rb");
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof serv_addr);
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;

    bind(serv_sd, (struct sockaddr *)&serv_addr, sizeof serv_addr);
    listen(serv_sd, 5);

    clnt_sd = accept(serv_sd, (struct sockaddr *)&clnt_addr, &clnt_adr_sz);
    
    while(1){
        memset(buf, 0, sizeof buf);
        read_cnt = fread((void *)buf, 1, BUF_SIZE, fp);
        printf("%s", buf);
        if(read_cnt < BUF_SIZE){
//            printf("-----\n");
//            printf("%s",buf);
            write(clnt_sd, buf, read_cnt + 1);
            break;
        }

        write(clnt_sd, buf, BUF_SIZE);

    }

    printf("\n%d\n", read_cnt);
    // 半关闭，关闭输出端
    shutdown(clnt_sd, SHUT_WR);
    read(clnt_sd, buf, BUF_SIZE);
    printf("Message from client: %s \n", buf);

    fclose(fp);
    close(clnt_sd);
    close(serv_sd);
    return 0;
}
