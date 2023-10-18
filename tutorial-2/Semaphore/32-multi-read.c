#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/ipc.h>
#include <fcntl.h>

/*
Objective : 
Write a program to implement semaphore to protect any critical section.
->protect multiple pseudo resources ( may be two) using counting semaphore
*/

void initialise();

union semun {
    int val; // Value for SETVAL 
};

void main(){

    //Uncomment it, if running it for the first time, to create 3-records.txt
    //initialise();
    int data;

    int fd = open("sample.txt", O_RDONLY);

    if(fd==-1){
        perror("error while opening file");
        exit(1);
    }

    int key;
    // Getting unique key
    if ((key = ftok("/tmp", 'B')) == -1) {
        perror("Error while generating key for semaphore");
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
    //Counting semaphore
    ss.val = 2;
    if (semctl(sem_id, 0, SETVAL, ss) == -1) {
        perror("Error while setting value to semaphore");
        exit(1);
    }

    printf("Semaphore created and initialized with key %d\n", key);

    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_flg = 0;
    sem_buf.sem_op = -1;

    printf("Before critical section, enter something to start process in critical section.\n");
	getchar();

    semop(sem_id, &sem_buf, 1); //Waiting call to get the access

	printf("Entered into critical section.\n");
    read(fd, &data, sizeof(int));
    printf("Data is : %d\n",data);
    printf("Enter something to come out of critical section:");
	getchar();
    getchar();

    sem_buf.sem_op = 1;
    semop(sem_id, &sem_buf, 1);

    printf("Exited critical section.\n");

    close(fd);
}

void initialise(){

    int fd = open("sample.txt", O_RDWR | O_CREAT, 0644);
	if(fd == -1){
		perror("Not able to open the file 'sample.txt'");
		exit(EXIT_FAILURE);
	}else{
		printf("Enter a integer: ");
		int a;
		scanf("%d",&a);
		write(fd, &a, sizeof(a));
		close(fd);
	}
}