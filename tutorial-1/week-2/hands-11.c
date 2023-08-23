#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* arg[]){
	
	if(argc!=2){
		printf("Pass required file-name with command\n");
		return 0;
	}
	int fd_source = open(arg[1], O_RDWR);
	int fd_dup = dup(fd_source);
	// in dup2() we can pass any fd as second integer based on our choice
	// it is already allocated to another file, 
	//it will be closed and allocated to this operation
	int fd_dup2 = dup2(fd_source, 10);
	
	int fd_fcntl;
	fd_fcntl = fcntl(fd_source, F_DUPFD);
	if(fd_fcntl<0){
		printf("Error duplicating file descriptor.\n");
		close(fd_source);
		close(fd_dup);
		close(fd_dup2);
		return 0;	
	}
	printf("Source fd by open(): %d", fd_source);
	printf("Duplicate-fd by dup(): %d\n", fd_dup);
	printf("Duplicate-fd by dup2(): %d\n", fd_dup2);
	printf("Duplicate-fd by fcntl(): %d\n", fd_fcntl);
	lseek(fd_source, 0, SEEK_END);
	printf("Appending with file-descriptor at end of the file\n");
	// we can write anything	
	char c = fd_source + '0';
	write(fd_dup, &c,1);
	c = fd_dup + '0';
	write(fd_dup2, &c,1);
	close(fd_source);
	close(fd_dup);
	close(fd_dup2);
	close(fd_fcntl);
	return 0;
}
