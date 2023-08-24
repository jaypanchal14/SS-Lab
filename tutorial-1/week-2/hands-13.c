#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	
	// Set of all fds'
	fd_set fdSet;
	
	fflush(stdout);
	
	//To flush all fds' from the set
	FD_ZERO(&fdSet);
	//We need to add STDIN's fd to the set
	FD_SET(0, &fdSet);
	
	//We need to wait for t seconds before reading from STDIN
	struct timeval timeVal;
	timeVal.tv_sec =5;
	
	printf("Data to be written on STDIN\n");
	// below operation returns the total number of fds' available from all the three set
	int value = select(1, &fdSet, NULL, NULL, &timeVal);
	printf("Number of total fds' after waiting period: %d\n", value);
	if(value==-1){
		perror("Error with select()\n");
	} else if(value){
		printf("Data available from STDIN\n");
	} else{
		printf("Defined wait is over, possible reason : No new connection were made or No data sent from existing connection/fd.\n");
	}
	
	return 0;
}
