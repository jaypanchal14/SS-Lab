#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

/*
Objective : (With 22-writer.c)
Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO. 
*/

void main(){

    char buf[100];
    
    int fd;
    //Opening to write to FIFO
    if((fd = open("ff-22", O_RDONLY))){
        perror("Not able to open fifo");
        exit(EXIT_FAILURE);
    }
    
	fd_set fdSet;
	fflush(stdout);
	
	//To flush all fds' from the set
	FD_ZERO(&fdSet);
	//We need to add STDIN's fd to the set
	FD_SET(fd, &fdSet);
	
	//We need to wait for t seconds before reading from STDIN
	struct timeval timeVal;
	timeVal.tv_sec = 10;

    int value = select(fd+1, &fdSet, NULL, NULL, &timeVal);
    if(value==-1){
		perror("Error with select()\n");
	} else if(value){
		printf("Data available from STDIN\n");
        read(fd, &buf, 100);
        printf("Message from 22-write.c : %s", msg);
	} else{
		printf("Defined wait is over, possible reason : No new connection were made or No data sent from existing connection(fd).\n");
	}

    close(fd);

}