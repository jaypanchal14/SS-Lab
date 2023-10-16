#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
Objective:
Write two programs so that both can communicate by FIFO (Two way communications with 21-a.c)
*/

void main(){

    int fd;

    if((fd = open("ff", O_RDWR))){
        perror("Not able to open fifo");
        exit(EXIT_FAILURE);
    }

    char msgRec[100];
    if(read(fd, &msgRec, 100)){
        perror("Error while reading from fifo");
        exit(EXIT_FAILURE);
    }

    printf("Message from 21-a.c: %s", msgRec);

    char msgSent[100];
    printf("Enter message to send: ");
    scanf("%[^\n]s", &msgSent);

    if(write(fd, msgSent, strlen(msgSent)) == -1){
        perror("Error while writing to the fifo");
        exit(EXIT_FAILURE);
    }

    close(fd);

}