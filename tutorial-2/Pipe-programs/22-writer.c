#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/*
Objective : (With 22-reader.c)
Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO. 
*/

void main(){

    char msg[100];

    //Uncomment this for creation of fifo
    /*if(mkfifo("ff-22", 0744)){
        perror("Not able to create fifo");
        exit(EXIT_FAILURE);
    }*/
    
    int fd;
    //Opening to write to FIFO
    if((fd = open("ff-22", O_WRONLY)) == -1){
        perror("Not able to open fifo");
        exit(EXIT_FAILURE);
    }
    printf("Enter message for 22-reader.c: ");
    scanf("%[^\n]s", msg);
    
    write(fd, msg, strlen(msg));
    close(fd);

}
