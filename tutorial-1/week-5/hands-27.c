#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

//Objective : To get familiar with exec() systel calls

void main(){
	
	char choice;
	printf("Enter any of the below command of your choice\n");
	printf("a)execl  b)execlp  c)execv  d)execvp  e)execle\n");
	scanf("%c",&choice);
	switch(choice){
		case 'a':
			execl("/bin/ls","ls","-RL",NULL);
			perror("execl");
			break;
		case 'b': 
			execlp("ls","ls","-RL",NULL);
			perror("execlp");
			break;
		case 'c': 
			char* argv[] = {"ls","-RL",NULL};
			execv("/bin/ls",argv);
			perror("execv");
			break;
		case 'd': 
			char* argp[] = {"ls","-RL",NULL};
			execvp("/bin/ls",argp);
			perror("execvp"); 
			break;
		case 'e': 
			char* env[] = {NULL};
			execle("/bin/ls","ls","-RL",NULL,env);
			perror("execle");
			break;
		default:
			printf("Wrong option selected\n");
			break;
	}

}
