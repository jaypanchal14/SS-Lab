#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Objective :
Write a program to find out total number of directories on the pwd.
execute : ls -l | grep ^d | wc 
(Use only dup2)
*/

void main(){

    //For executing first command
    int ls[2];
    //For executing second command
    int grep[2];

    if(pipe(ls) == -1){
        perror("Error while creating first pipe");
        exit(EXIT_FAILURE);
    }

    int pId = fork();
    if(pId){
        //Parent process
        close(ls[1]);
        dup2(ls[0], 0);  // STDIN_FILENO (0)
        close(ls[0]);
        sleep(1);
        if(pipe(grep) == -1){
            perror("Error while creating second pipe");
            exit(EXIT_FAILURE);
        }

        int secondP = fork();
        if(secondP){
            //Parent process
            close(grep[1]);
            dup2(grep[0],0);
            close(grep[0]);
            execlp("wc", "wc", "-l", NULL);

        }
        else{
            //Child's child process
            close(grep[0]);
            dup2(grep[1],1);
            close(grep[1]);
            execlp("grep", "grep", "^d", NULL);
        }
        
        
    }
    else{
        //Child process
        close(ls[0]);
        //Copy to 
        dup2(ls[1], 1);  // STDOUT_FILENO (1)
        close(ls[1]);

        execlp("ls", "ls", "-l", NULL);

    }
}