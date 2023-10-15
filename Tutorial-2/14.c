#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/*
Objective :
Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
*/

void main(){
    
    // p[0] : fd for reading, p[1] : fd for writing
    int p[2];

    if(pipe(p) == -1){
        perror("Error while creating pipe");
        exit(EXIT_FAILURE);
    }
    
    char* s = "message for pipe";
    write(p[1],s,strlen(s));
    char buf[64];
    read(p[0], &buf, sizeof(buf));
    printf("Message from pipe: %s",buf);

}