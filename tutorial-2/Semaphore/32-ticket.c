#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

/*
Objective : 
Write a program to implement semaphore to protect any critical section.
->rewrite the ticket number creation program using semaphore
(d)remove the created semaphore
*/

void initialise();

union semun {
    int val; // Value for SETVAL    
};

void main(){

    //Uncomment it, if running it for the first time, to create 3-records.txt
    //initialise();

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
  
    //Binary semaphore
    ss.val = 1;
    
    if (semctl(sem_id, 0, SETVAL, ss) == -1) {
        perror("Error while setting value to semaphore");
        exit(1);
    }

    printf("Semaphore created and initialized with key %d\n", key);

	struct sembuf buf;
    buf.sem_num = -1;  //This value would be added to the current value of semaphore
    buf.sem_flg = 0;

	printf("Before critical section, enter something to start process in critical section.\n");
	getchar();

	semop(sem_id, &buf, 1); //Waiting call to get the access
	printf("Entered into critical section.\n");

	//File opening
	int fd = open("3-records.txt", O_RDWR, 0644);
	int a,b,c;
	if(fd == -1){
		perror("Not able to open the file '3-records.txt'");
		exit(EXIT_FAILURE);
	}else{
		read(fd, &a, sizeof(a));
		read(fd, &b, sizeof(b));
		read(fd, &c, sizeof(c));
		printf("Current values of records:\n1)a: %d\n2)b: %d\n3)c: %d\n",a,b,c);

	}

	printf("Select record number (either 1 or 2 or 3): ");
	int record, start;
	scanf("%d",&record);
	fflush(stdin);
	fflush(stdout);
	if(record == 1 || record == 2 || record == 3){
		start = (record-1)*sizeof(record);
	}
	else{
		printf("Not valid record number\n");
		exit(EXIT_FAILURE);
	}
	lseek(fd, start, SEEK_SET);

	if(record == 1){
		a++;
		write(fd, &a, sizeof(int));
	
	}else if (record == 2){
		b++;
		write(fd, &b, sizeof(int));
	
	}else{
		c++;
		write(fd, &c, sizeof(int));

	}
	
	printf("Enter something to come out of critical section:");
	getchar();
	getchar();

	buf.sem_op = 1;
    semop(sem_id, &buf, 1);

	printf("Exited critical section.\n");

}

void initialise(){

    int fd = open("3-records.txt", O_RDWR | O_CREAT, 0644);
	if(fd == -1){
		perror("Not able to open the file '3-records.txt'");
		exit(EXIT_FAILURE);
	}else{
		printf("Enter three different integers separated by a single space");
		int a,b,c;
		scanf("%d %d %d", &a, &b, &c);
		write(fd, &a, sizeof(a));
		write(fd, &b, sizeof(b));
		write(fd, &c, sizeof(c));
		close(fd);
	}
}