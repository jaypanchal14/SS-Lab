#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

/*
Objective:
Write a program to print a message queue's properties(use msqid_ds and ipc_perm structures)
*/

void main(){
    int key;
    // Getting unique key for the message queue
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("Error while creating a key");
        exit(1);
    }

    int msg_id;
    // Create a message queue with read and write permissions
    if ((msg_id = msgget(key, 0744 | IPC_CREAT)) == -1) {
        perror("Error while creating msg-queue");
        exit(1);
    }

    struct msqid_ds info;

    // Get information about the message queue
    if (msgctl(msqid, IPC_STAT, &info) == -1)
    {
        perror("Error while executing msgctl");
    }

    //(a)Access permission
    printf("Access Permission: %o\n", info.msg_perm.mode);

    //(b)UID and GID
    printf("UID: %d\n", info.msg_perm.uid);
    printf("GID: %d\n", info.msg_perm.gid);

    //(c)Time of last message sent and received
    printf("Time of Last Message Sent: %s", ctime(&info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&info.msg_rtime));

    //(d)Time of last change in the message queue
    printf("Time of Last Change in Queue: %s", ctime(&info.msg_ctime));

    //(e)Size of the queue
    printf("Size of Queue in bytes: %ld\n", info.msg_qbytes);

    //(f)Number of messages in the queue
    printf("Number of Messages in Queue: %ld\n", info.msg_qnum);

    //(g)Maximum number of bytes allowed
    printf("Maximum Number of Bytes Allowed: %ld\n", info.msg_qbytes);

    //(h)PID of the msgsnd and msgrcv
    printf("PID of Last msgsnd: %d\n", info.msg_lspid);
    printf("PID of Last msgrcv: %d\n", info.msg_lrpid);

}