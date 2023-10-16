#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
Objective:
Write a program to change the exiting message queue permission. (use msqid_ds structure)
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

    struct msqid_ds info;
    // Retrieve current message queue settings
    if (msgctl(msqid, IPC_STAT, &queueInfo) == -1) {
        perror("Error while fecthing queue-info");
        exit(1);
    }

    //Updating the permission
    info.msg_perm.mode = 0777;

    if (msgctl(msq_id, IPC_SET, &info) == -1) {
        perror("Error while setting queue-info");
        exit(1);
    }

    printf("Message queue permissions updated.\n");

}