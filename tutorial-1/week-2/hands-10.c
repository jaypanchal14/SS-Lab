#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	printf("Enter a file-name: \n");
	char fileName[100];
	scanf("%s",fileName);
	printf("FileName: %s\n",fileName);
	int fd = open(fileName, O_RDWR);
	int count = 9;
	char c;
	printf("Writing 10 bytes of data in file\n");
	while(count>=0){
		c = count + '0';
		write(fd, &c, 1);
		count--;
	}
	
	//Skipping next 10 characters from the end of the file
	printf("Skipping 10 characters in file\n");
	off_t seekResp = lseek(fd, 10, SEEK_CUR);
	printf("Current position in file: %ld\n",seekResp);
	
	while(count<10){
		count++;
		c = count + '0';
		write(fd, &c, 1);
		
	}
	
	/*
	//Example of SEEK_SET to change the current position to absolute position/offset
	lseek(fd,8,SEEK_SET);
	char c;
	while(read(fd,&c,1)){
		write(1,&c,1);
	}*/
	close(fd);
	return 0;
}
