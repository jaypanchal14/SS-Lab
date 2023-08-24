#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* arg[]){
	
	if(argc!=2){
		printf("Need to pass one file-name along with executable file.\n");
	}
	
	struct stat st;
	stat(arg[1], &st);
	
	if(S_ISDIR(st.st_mode)){
		printf("File is: DIRECTORY\n");
	}
	else if(S_ISCHR(st.st_mode)){
		printf("File is: CHARACTER DEVICE\n");
	}
	else if(S_ISBLK(st.st_mode)){
		printf("File is: BLOCK DEVICE\n");
	}
	else if(S_ISLNK(st.st_mode)){
		printf("File is: SYMBOLIC LINK\n");
	}
	else if(S_ISREG(st.st_mode)){
		printf("File is: REGULAR FILE\n");
	}
	else if(S_ISFIFO(st.st_mode)){
		printf("File is: FIFO OR NAMED PIPE\n");	
	}
	else if(S_ISSOCK(st.st_mode)){
		printf("File is: SOCKET FILE\n");
	}
	else{
		printf("File type can't defined.\n");
	}
	
	return 0;
}
