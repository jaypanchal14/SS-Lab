#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

//Objective : to use parent and child process to write to the same file.

void main(){
	
	//Objective : to open a file and write from parent and child process both.
	int fd = open("22-fork.txt", O_RDWR | O_CREAT, 0644);
	
	int pid = fork();
	
	if(pid == 0){
		// by child process
		char* c = "by child process\n";
		write(fd,c,strlen(c));
	}
	else{
		// by parent process
		char* p = "by parent process\n";
		write(fd,p,strlen(p));
		
	}
	
	close(fd);
}
