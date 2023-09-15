#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

// Objective : to give example of zombie process
//Zombie process : a process which has completed its execution but
// it still has the resources allocated and an entry in the file descriptor table

void main(){
	
	int pid = fork();
	
	if(pid == 0){
		printf("Child process-id : %d\n",getpid());
		exit(0);
		
	}
	else{
		printf("Parent process-id : %d\n",getpid());
		sleep(30);
	}

}
