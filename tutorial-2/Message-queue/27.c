#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
Objective:
Write a program to receive messages from the message queue.
(a) with 0 as a flag    (b) with IPC_NOWAIT as a flag
*/

struct msgbuf{
    long mtype;     
    char text[100];
};

void main(){
    
    int key;
    // Getting unique key for the message queue
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("Error while generating key");
        exit(1);
    }

    int msg_id;
    // Create a message queue with read and write permissions
    if ((msg_id = msgget(key, 0744 | IPC_CREAT)) == -1) {
        perror("Error while creating msg-queue");
        exit(1);
    }

    struct msgbuf mm;
    //As we have set mm.type as '1', we are passing 4th parameter as 1.
    //As we have sent a message using 26.c, we will run this program to receive the same message
    //(a) with 0 as a flag -> it will wait, till we get the message from the queue [Blocking call]
    while(1){
        if (msgrcv(msg_id, &mm, sizeof(mm.text), 1, 0) == -1) {
            perror("Error while receiving message from queue");
            exit(1);
        }
        printf("Received message: %s\n", mm.text);
    }

    //(b)with IPC_NOWAIT as a flag. [Non-blocking call]
    /*
    while(1){
        if (msgrcv(msg_id, &mm, sizeof(mm.text), 1, IPC_NOWAIT) == -1) {
            perror("Error while receiving message from queue");
            exit(1);
        }
        printf("Received message: %s\n", mm.text);
    }
    */

}