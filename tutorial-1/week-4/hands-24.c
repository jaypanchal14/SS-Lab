#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

// Objective : to create an orphan process
// Orphan process : it is a process whose parent process exists before
// 					its completion. So, it will be adopted by init process.

void main(){
	
	int pid = fork();
	
	if(pid == 0){
		printf("Child process-id : %d\n",getpid());
		printf("Child's parent process-id : %d\n",getppid());
		sleep(5);
		printf("Child's parent process-id : %d\n",getppid());
		
	}
	else{
		printf("Parent process-id : %d\n",getpid());
		printf("My child process-id : %d\n",pid);
		sleep(2);
		exit(0);
	}
	
	
}
