#include <stdio.h>
#include <unistd.h>

int main(){
	
	char message[10] = "0123456789";
	write(1, message,10);
	printf("\nWritten to STDOUT stream.\n");
	read(1, message,10);
	printf("Read from STDIN stream into buffer(char-array) message.\n");
	return 0;
}
