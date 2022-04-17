#include<stdio.h>
#include<fcntl.h>

int main(){
    FILE *fp;
    int fd = open("news1.dat", O_RDWR | O_CREAT | O_TRUNC);
    if(fd == -1){
        fputs("open() error!\n", stdout);
        return -1;
    }
    printf("First file descriptor: %d \n", fd);
    fp = fdopen(fd, "w");
    fputs("Are you ready to dance?\n", fp);
    printf("Second file descriptor: %d \n", fileno(fp));
    fclose(fp);
    return 0;
}