#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
	char* fileName = "createFile";
	// As we have given O_EXCL : it will prevent from creating the file
	// if it doesn't exist
	mode_t mode = O_RDWR | O_EXCL;
	int fd = open(fileName, mode);
	printf("File opened with descriptor:%d\n",fd);
	if(fd<0){	
		perror("File can't be opened.");
	}
	return 0;
}
