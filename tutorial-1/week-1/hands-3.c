#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	
	char* name = "createFile";
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int fd = creat(name, mode);
	// we can also create a file with below line
	//int fd = creat(name, 0644);
	printf("File created with descriptor : %d\n",fd);
	return 0;
}
