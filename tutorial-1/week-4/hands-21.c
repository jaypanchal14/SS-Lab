#include<stdio.h>
#include<unistd.h>

//Objective : To use fork to create child process.

void main(){
	
	//used to create a child process
	int processId = fork();
	//above will return an int which will have 0 for child-process
	//and non-zero for parent
	if(processId==0){
		printf("Child process-id : %d\n",getpid());
	}
	else{
		printf("Parent process-id : %d\n",getpid());
	}

}
