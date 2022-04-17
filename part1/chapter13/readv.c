#include<stdio.h>
#include<sys/uio.h>
#define BUF_SIZE 30
int main(int argc, char *argv[]){

    char buf[BUF_SIZE] = {0,};
    char buf1[BUF_SIZE] = {0,};

    int str_len;

    struct iovec vec[2];
    vec[0].iov_base = buf;
    vec[0].iov_len = 5;
    vec[1].iov_base = buf1;
    vec[1].iov_len = BUF_SIZE;

    str_len = readv(0, vec, 2);
    printf("Read Bytes: %d \n", str_len);
    printf("first message : %s \n", buf);
    printf("second message : %s \n", buf1);

    return 0;
}