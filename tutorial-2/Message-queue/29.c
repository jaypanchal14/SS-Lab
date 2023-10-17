#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
Objective:
Write a program to remove the message queue.
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
    if ((msg_id = msgget(key, 0777 | IPC_CREAT)) == -1) {
        perror("Error while creating msg-queue");
        exit(1);
    }

    if (msgctl(msg_id, IPC_RMID, NULL) == -1) {
        perror("Error while deleting queue");
        exit(EXIT_FAILURE);
    }

    printf("Message-queue is deleted.\n");
    
}
