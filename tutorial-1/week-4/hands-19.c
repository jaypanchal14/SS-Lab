#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

//Objective : 
// To print the execution time of the operation using
// the time-stamp-counter (assembly level register)
// In order to read from the assembly level register, we need an assembly level function too
// it will return the number of clock-cycles spent till execution

static inline uint64_t rdtsc(){
	uint32_t low, high;
	__asm__ volatile(
		"rdtsc" : "=a" (low), "=d" (high)
	);
	return ((uint64_t)high<<32) | low;
}

void main(){
	uint64_t start,end;
	double timeTaken;
	uint64_t freq;
	
	start = rdtsc();
	sleep(1);
	end = rdtsc();
	freq = end-start;
	
	//Intended calculation of execution time of the operation
	start = rdtsc();
	
	printf("Process-id : %d\n",getpid());
	end = rdtsc();
	timeTaken = (double)(end-start)/freq;
	printf("Time taken to get the process-id: %f\n", timeTaken);
}
