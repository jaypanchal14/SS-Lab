#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* arg[]){

	if(argc!=3){
		printf("Not enough argument passed while executing.\n");
		return -1;
	}	
	int fd_source = open(arg[1], O_RDONLY);
    int fd_dest = open(arg[2], O_WRONLY|O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd_source==-1 || fd_dest==-1){
		printf("Not able to open the file\n");
	}
	//To read from source and write to destination
	while(1){
		char buf;
		int byte = read(fd_source, &buf, 1);
		if(byte!=1){
			break;
		}
		write(fd_dest, &buf, 1);
	}
	printf("File copied from source to destination\n");
	int close_source = close(fd_source);
	int close_dest = close(fd_dest);
	if(close_source == -1 || close_dest == -1){
		printf(" Not able to close the file\n");
	}
	return 0;
}
