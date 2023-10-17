#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

/*
Objective:
Write a program to send messages to the message queue(Check $ipcs -q).
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
    // Create a message queue with read and write permissions (IPC_CREAT : if it doesn't exits, it creates)
    if ((msg_id = msgget(key, 0744 | IPC_CREAT)) == -1) {
        perror("Error while creating msg-queue");
        exit(1);
    }

    struct msgbuf mm;
    mm.mtype = 1;
    strcpy(mm.text, "First msg to queue");

    // Send the message to the queue
    if (msgsnd(msg_id, &mm, sizeof(mm.text), 0) == -1) {
        perror("Error while sending message on queue");
        exit(1);
    }
    printf("Message is sent, check with command -> 'ipcs -q'\n");

    //To delete a message from the message queue using msq-id
    // run command -> ipcrm -q <id>   (you can get the id from the command 'ipcs -q')

}
