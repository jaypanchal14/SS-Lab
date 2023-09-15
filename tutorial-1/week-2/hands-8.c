#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//Objective : Write a program to open a file in read only mode, 
//			  read line by line and display each line as it is read.
//			  Close the file when end of file is reached.

int main(int argc, char* arg[]){

	if(argc!=2){
		printf("Not enough argument passed while executing.\n");
		return -1;
	}	
	int fd_source = open(arg[1], O_RDONLY);
    if(fd_source==-1){
		printf("Not able to open the file\n");
		exit(1);
	}
	//To read from source line by line and print to console
	char buf[128];
	while(read(fd_source, &buf,sizeof(buf))){
		printf("%s",buf);
	}
	int close_source = close(fd_source);
	if(close_source == -1){
		printf(" Not able to close the file\n");
	}
	return 0;
}
