#include<string.h>
#include<stdlib.h>
#include<sys/uio.h>
#include<stdio.h>

int main(){
    struct iovec vec[2];
    char buf[7] = "ABCDEF";
    char buf1[7] = "123456";
    vec[0].iov_base = buf;
    vec[0].iov_len = 3;
    vec[1].iov_base = buf1;
    vec[1].iov_len = 4;
    ssize_t size = writev(1, vec, 2);
    puts("");
    printf("Write bytes: %ld \n", size);
    return 0;
}