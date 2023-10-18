#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

/*
Objective:
Program to remove the created semaphore.
*/

void main(){
    int key;
    // Getting unique key
    if ((key = ftok("/tmp", 'B')) == -1) {
        perror("Error while generating key for semaphore");
        exit(1);
    }

    int sem_id;

    // Create a semaphore with a specified key and permissions
    // arguments : unique-key, size of set-of-semaphores, permissions
    if ((sem_id = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("Error while creating semaphore");
        exit(1);
    }

    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("Error while deleting semaphore");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore with id: %d is deleted.\n",sem_id);
}