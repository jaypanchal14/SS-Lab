#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>

/*
Objective :
Write a program to create a message queue and print the key and message queue id.
*/

void main(){

    int key;
    // Getting unique key for the message queue
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("Error while generating key");
        exit(1);
    }

    int msg_id;
    // Create a message queue with read and write permissions (IPC_CREAT : if it doesn't exits, it creates)
    if ((msg_id = msgget(key, 0744 | IPC_CREAT)) == -1) {
        perror("Error while creating msg-queue");
        exit(1);
    }

    //Check if the data-type is correct or not, otherwise use 0x%x
    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msg_id);
}