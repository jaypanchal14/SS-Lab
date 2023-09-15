#include<stdio.h>
#include<sys/resource.h>
#include<unistd.h>

//Objective : To find and modify the priority of the process.

void main(){
	//To get the priority of the running process
	int currPrio;
	
	//it can take process or group or user as first argument and 
	//second argument is zero, which means current process
	currPrio = getpriority(PRIO_PROCESS, 0);
	printf("Priority of current process : %d\n", currPrio);
	
	//to update the priority by passed argument
	// here, it will add 10 to current priority which is by-default '0'
	nice(10);
	
	int newPrio = getpriority(PRIO_PROCESS, 0);
	printf("New priority of current process : %d\n", newPrio);
	fflush(stdin);
	getchar();
	
}
