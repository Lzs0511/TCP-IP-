#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<stdio.h>

int main(int argc, char *argv[]){

    struct sockaddr_in addr1, addr2;
    addr1.sin_addr.s_addr = htonl(0x10030201);
    addr2.sin_addr.s_addr = htonl(0x11030201);

    char *str_ptr;
    char str_add[30];

    str_ptr = inet_ntoa(addr1.sin_addr);
    // if(str_ptr != -1)
    printf("Dotted-Decimal notation1: %s\n", str_ptr);
    strcpy(str_add, str_ptr);
    str_ptr = inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s\n", str_ptr);
    printf("Dotted-Decimal notation3: %s\n", str_add);
    return 0;
}