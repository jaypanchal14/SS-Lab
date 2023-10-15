#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/*
Objective :
Write a program to execute -> ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
*/

void main(){

    int p[2];

    if(pipe(p) == -1){
        perror("Error while creating pipe");
        exit(EXIT_FAILURE);
    }

    int pId = fork();
    if(pId != 0){
        //Parent process
        close(p[1]);
        close(0);
        //So, 0 will get value from p[0]
        dup(p[0]);
        sleep(1); //Need to check this
        execlp("wc", "wc", NULL);

    }
    else{
        //Child process
        close(p[0]);
        
        //If using dup2 system call
        dup2(p[1],1);
        
        //If using fcntl function to duplicate descriptor, uncomment below
        /*close(1);
        fcntl(p[1],F_DUPFD,1);*/
        execlp("ls", "ls", "-l", NULL);

    }


}