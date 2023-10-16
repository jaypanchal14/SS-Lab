#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
Objective:
Write a program to create a semaphore and initialize value to the semaphore.
(a)create a binary semaphore
(b)create a counting semaphore
*/

union semun {
    int val; // Value for SETVAL    
};

void main() {

    int key;
    // Getting unique key
    if ((key = ftok("/tmp", 'B')) == -1) {
        perror("Error while generating key");
        exit(1);
    }
  
    int sem_id;
    union semun ss;

    // Create a semaphore with a specified key and permissions
    // arguments : unique-key, size of set-of-semaphores, permissions
    if ((sem_id = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("Error while creating semaphore");
        exit(1);
    }
  
    // Set the semaphore value to 1 (or any other initial value)
    ss.val = 1; //Binary semaphore

    //ss.val = 3; //Counting semaphore with maximum 3 entry in critical section
    // Initialize the semaphore value using semctl
    // argument: semaphore-identifier, set-index, command, union object
    if (semctl(sem_id, 0, SETVAL, ss) == -1) {
        perror("Error while setting value to semaphore");
        exit(1);
    }

    printf("Semaphore created and initialized with key %d\n", key);

    // Remove the semaphore
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("Error while removing semaphore");
        exit(1);
    }

    printf("Semaphore deleted.\n");
}
