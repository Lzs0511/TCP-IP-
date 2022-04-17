#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
int main(int argc, char *argv[]){

    int sock;
    char opmsg[BUF_SIZE];
    int result, opnd_cnt, i;

    struct sockaddr_in serv_addr;
    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if(sock == -1){
        perror("socket");
        exit(2);
    }

    memset(&serv_addr, 0, sizeof serv_addr);
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof serv_addr) == -1){
        perror("connect");
        exit(3);
    }else{
        puts("Connected...\n");

        fputs("Operand count: ", stdout);
        scanf("%d", &opnd_cnt);

        opmsg[0] = (char)opnd_cnt;
        printf("%d\n", opmsg[0]);
        for(i = 0; i < opnd_cnt; i++){
            printf("Operand %d: ", i + 1);
            scanf("%d", (int *)&opmsg[OPSZ * i + 1]);
        }

        fgetc(stdin);
        fputs("Operator: ", stdout);
        scanf("%c", &opmsg[opnd_cnt * OPSZ + 1]);
        write(sock, opmsg, opnd_cnt * OPSZ + 2);
        read(sock, &result, RLT_SIZE);
        printf("Operation result: %d\n ", result);
        close(sock);
    }



    return 0;
}
