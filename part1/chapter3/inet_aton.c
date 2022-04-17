#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
int main(){

    const char *addr = "192.168.1.1";

    struct sockaddr_in saddr;
    if(!inet_aton(addr, &saddr.sin_addr)){
        perror("inet_aton");
        exit(1);
    }else{
        printf("Network ordered integer addr: %#x \n", saddr.sin_addr.s_addr);
    }
    return 0;
}