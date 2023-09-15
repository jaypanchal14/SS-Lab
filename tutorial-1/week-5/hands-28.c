#include<stdio.h>
#include<sched.h>

// Objective : to get the min and max priority of the real-time
//             scheduling process

void main(){
	
	//First in first out pattern
	int maxP, minP;
	maxP = sched_get_priority_max(SCHED_FIFO);
	minP = sched_get_priority_min(SCHED_FIFO);
	
	printf("Maximum real-time priority : %d\n",maxP);
	printf("Minimum real-time priority : %d\n",minP);
	
	// Round-robin fashion
	//maxP = sched_get_priority_max(SCHED_RR);
	//minP = sched_get_priority_min(SCHED_RR);
	//printf("Maximum real-time priority : %d\n",maxP);
	//printf("Minimum real-time priority : %d\n",minP);

}
