#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/*
Objective:
Write a simple program to send some data from parent to the child process.
*/

void main(){

    int p[2];
    int pId;
    
    if(pipe(p) == -1){
        perror("Error while creating pipe");
        exit(EXIT_FAILURE);
    }

    pId = fork();

    //We are closing one end from each process, so no process works unexpected.

    if(pId != 0){
        //Parent process
        close(p[0]);
        char* msg= "Hi Child.";
        write(p[1],msg,strlen(msg));
		printf("Message sent to child.\n");
		close(p[1]);

    }
    else{
        //Child process
        close(p[1]);
        char buf[100];
        read(p[0], &buf, 100);
        printf("Message received from parent: %s\n",buf);
		close(p[0]);
    }


}