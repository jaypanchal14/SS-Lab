#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/*
Objective : To have two-way communication using fifo with 20-a.c program.
*/

void main(){

    char buf[100];
    
    int fd;
    //Opening to readf from FIFO
    if((fd = open("ff", O_RDONLY))){
        perror("Not able to open fifo");
        exit(EXIT_FAILURE);
    }

    read(fd, &buf, sizeof(buf));

    printf("From 20-a.c : %s",buf);
}