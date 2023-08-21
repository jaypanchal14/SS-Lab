#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//Driver code : it will take main-target file, expected soft-link and hard-link file-name
// in the execution command (in arg[])
int main(int argc, char* arg[]){
	
	printf("Number of arguments:%d\n",argc);
	if(argc==4){
		// To create soft-link via cmd : ln -s <file> <soft-link-file-name>
		int softL = symlink(arg[1],arg[2]);
		if(softL==0)
		{	printf("Soft-link created successfully\n"); }
		else
		{	perror("Soft-link not created, gave error\n");}
	
		// To create hard-link via cmd : ln <file> <hard-link-file-name>
		int hardL = link(arg[1],arg[3]);
		if(hardL==0){
		{	printf("Hard-link created successfully\n"); }
		}
		else
		{	perror("Hard-link not created, gave error\n");}
		
		// To create a FIFO (named-pipe) mkfifo <name>
		int fifo = mkfifo("myFifo",0666);
		if(fifo==0){
		{	printf("Named pipe created successfully\n"); }
		}
		else
		{	perror("Named pipe not created, gave error\n");}
	}
	else{
		printf("Pass required arguments, currently it will not work\n");
	}
	return 0;
}
