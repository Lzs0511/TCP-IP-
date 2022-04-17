#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]){

    unsigned short host_endian_short = 0x1234;
    unsigned long host_endian_long = 0x12345678;
    unsigned short net_endian_short = htons(host_endian_short);
    unsigned long net_endian_long = htonl(host_endian_long);

    printf("host endian order port: %hx\n", host_endian_short);
    printf("host endian order address: %lx\n", host_endian_long);
    printf("network endian order port: %hx\n", net_endian_short);
    printf("network endian order address: %lx\n", net_endian_long);

    return 0;
}