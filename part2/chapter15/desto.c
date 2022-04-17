#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){
    FILE *fp;
    int fd = open("news.dat", O_WRONLY | O_CREAT | O_TRUNC);
    if(fd == -1){
        fputs("file open error", stdout);
        return -1;
    }
    fp = fdopen(fd, "w");
    fputs("Are you ready to dance?\n", fp);
    fclose(fp);
    return 0;
}