#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/*
Objective : To have two-way communication using fifo with 20-b.c program.
*/

void main(){

    char* msg = "Message from 20-a.c";

    if(mkfifo("ff", 0744)){
        perror("Not able to create fifo");
        exit(EXIT_FAILURE);
    }
    
    int fd;
    //Opening to write to FIFO
    if((fd = open("ff", O_WRONLY))){
        perror("Not able to open fifo");
        exit(EXIT_FAILURE);
    }

    write(fd, msg, strlen(msg));
    close(fd);

}