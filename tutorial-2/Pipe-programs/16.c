#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/*
Objective:
Write a program to send and receive data from parent to child vice-versa. Use two way communication.
*/

void main(){
    int p2c[2];
    int c2p[2];

    if(pipe(p2c) == -1){
        perror("Error while creating parent-to-child pipe");
        exit(EXIT_FAILURE);
    }

    if(pipe(c2p) == -1){
        perror("Error while creating child-to-parent pipe");
        exit(EXIT_FAILURE);
    }

    int pId = fork();

    if(pId != 0){
        //Parent process
        close(p2c[0]);
        close(c2p[1]);

        char* msg = "Hi child.";
        write(p2c[1], msg, strlen(msg));
        char buf[200];
        read(c2p[0], &buf, 200);
        printf("Message received at parent from child : %s",buf);

        close(p2c[1]);
        close(c2p[0]);

    }
    else{
        //Child process
        close(p2c[1]);
        close(c2p[0]);

        char buf[200];
        read(p2c[0], &buf, 200);
        printf("Message received at child from parent : %s",buf);
        char* msg = "Hi parent.";
        write(p2c[1], msg, strlen(msg));

        close(p2c[0]);
        close(c2p[1]);

    }

}