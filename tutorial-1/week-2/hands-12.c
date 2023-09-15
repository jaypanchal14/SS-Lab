#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Objective : to print the opening mode of the file using fcntl system call

int main(int argc, char** arg){

	//Program to return the access mode of the file
	if(argc!=2){
		printf("Need to pass one file name with the command during execution.\n");
	}
	
	// O_RDONLY, O_WRONLY, O_RDWR
	int fd = open(arg[1],O_RDONLY);
	if(fd==-1){
		printf("Error opening the file\n");
		return 0;
	}
	//To get the the mode of file with fcntl system call
	int flag = fcntl(fd, F_GETFL) & O_ACCMODE;
	if(flag==0){
		printf("File is opened in read-only mode.\n");
	} else if(flag==1){
		printf("File is opened in write-only mode.\n");
	} else if(flag==2){
		printf("File is opened in read-write mode.\n");
	} else{
		printf("File is opened in other mode.\n");
	}
	close(fd);
	return 0;
}
