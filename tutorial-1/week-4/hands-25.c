#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>

//Objective : to create three child processes

void main(){
	
	int status;
	int pid1 = fork();
	
	if(pid1 == 0){
		printf("First child process-id : %d\n",getpid());
		printf("First child's parent process-id : %d\n",getppid());
		sleep(1);
	}
	else{
		
		//this function wait for the child's process to change its status first.
		// -1 indicates the child process of the current process
		waitpid(-1, &status, 0);
		int pid2 = fork();
		if(pid2 == 0){
			printf("Second child process-id : %d\n",getpid());
			printf("Second child's parent process-id : %d\n",getppid());
			sleep(1);
		}
		else{
			waitpid(-1, &status, 0);
			int pid3 = fork();
			if(pid3 == 0){
				printf("Third child process-id : %d\n",getpid());
				printf("Third child's parent process-id : %d\n",getppid());
				sleep(1);
			}
			else{
				waitpid(-1, &status, 0);
				printf("All three child processes has completed their execution under the parent process : %d\n",getpid());
			}
		}
	}
}
