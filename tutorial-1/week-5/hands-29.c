#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sched.h>

//Objective : a program to get scheduling policy and 
//			  modify the scheduling policy (SCHED_FIFO,SCHED_RR)

void main(){
	
	int pid = getpid();
	
	//to get the current scheduling policy
	// here, 0 indicates the calling process
	int currentPolicy = sched_getscheduler(0);
	
	if(currentPolicy == -1){
		printf("Error while getting current scheduling policy");
		exit(0);
	}	
	
	printf("Current scheduling policy is %d : ",currentPolicy);
	switch(currentPolicy){
		case SCHED_FIFO :
			printf("SCHED_FIFO\n");
			break;	
		case SCHED_RR :
			printf("SCHED_RR\n");
			break;
		case SCHED_OTHER :
			printf("SCHED_OTHER\n");
			break;
		default :
			printf("Unknown policy\n");
			break;
	}
	
	struct sched_param param;
	param.sched_priority = 10;
	if(sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
		perror("ERROR setting SCHED_FIFO policy");
		exit(EXIT_FAILURE);
	}
	
	printf("Scheduling policy changed to SCHED_FIFO\n");
	int newPolicy = sched_getscheduler(getpid());
	printf("New scheduling policy is %d :",currentPolicy);
	switch(newPolicy){
		case SCHED_FIFO :
			printf("SCHED_FIFO\n");
			break;	
		case SCHED_RR :
			printf("SCHED_RR\n");
			break;
		case SCHED_OTHER :
			printf("SCHED_OTHER\n");
			break;
		default :
			printf("Unknown policy\n");
			break;
	}

}
