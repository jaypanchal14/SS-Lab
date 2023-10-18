#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/ipc.h>

/*
Objective : 
Write a program to implement semaphore to protect any critical section.
->protect shared memory from concurrent write access
*/

union semun {
    int val; // Value for SETVAL 
};

void main(){

    int key, key_m;
    // Getting unique key
    if ((key = ftok("/tmp", 'B')) == -1) {
        perror("Error while generating key for semaphore");
        exit(1);
    }
    // Getting unique key
    if ((key_m = ftok("/tmp", 'C')) == -1) {
        perror("Error while generating key for shared-memory");
        exit(1);
    }
  
    int sem_id, shm_id;
    union semun ss;

    // Create a semaphore with a specified key and permissions
    // arguments : unique-key, size of set-of-semaphores, permissions
    if ((sem_id = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("Error while creating semaphore");
        exit(1);
    }
    //Binary semaphore
    ss.val = 1;
    if (semctl(sem_id, 0, SETVAL, ss) == -1) {
        perror("Error while setting value to semaphore");
        exit(1);
    }

    printf("Semaphore created and initialized with key %d\n", key);

    if((shm_id = shmget(key_m, 1024, IPC_CREAT|0744)) == -1){
        perror("Error while creating memory-segment");
        exit(1);
    }
    
    char* addr = (char*)shmat(shm_id, NULL,0);
    if (addr == (void *)-1) {
        perror("Error while attaching memory segment");
        exit(1);
    }

    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = 0;
    sem_buf.sem_op = -1;

    printf("Before critical section, enter something to start process in critical section.\n");
	getchar();

    semop(sem_id, &sem_buf, 1); //Waiting call to get the access
	printf("Entered into critical section.\n");
    printf("Current value of memory-segment : %s\n",addr);
    char buf[1024];
    printf("Enter value to store in memory-segment: ");
    scanf("%s", buf);
    memset(addr,0,1024);
    strcpy(addr, buf);

    printf("Enter something to come out of critical section:");
	getchar();

    printf("\nData from the memory-segment: %s\n",addr);

    sem_buf.sem_op = 1;
    semop(sem_id, &sem_buf, 1);

	printf("Exited critical section.\n");

}