#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

//Objective : 
//Write a program to execute an executable program.
//a. use some executable program (here, we are using C-program)
//b. pass some input to an executable program. (for example execute an executable of $./a.out name)

//Before running this file, please prepare one executable file doing some work.
//Here, I am using question 'hands-21' from week-4, and i would run the command as 
// i.e.,  './hands-28 hands-21'

void main(int argc, char** argv){
	
	//TODO : take input and execute it using exec library call
	if(argc!=2){
		printf("Need to pass exactly one executable file-name along with the command.\n");
		exit(1);
	}
	printf("Do you want to run 'ls' command, if yes: Enter 1, otherwise Enter any other number: ");
	int choice;
	scanf("%d",&choice);
	if(choice==1){
		execl("/bin/ls","ls","-l",NULL);
	}
	else{
		printf("Going to execute %s",argv[1]);
		char* ar[] = {argv[1], NULL};
		execv(ar[0], ar);
		
	//Will not print below line, as execl command will replace the existing process's image
	//with the new process image which it will call at line-25;
		printf("Execution completed");	
	}
	
}
