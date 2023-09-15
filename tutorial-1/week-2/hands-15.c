#include <stdio.h>

//Objective : to print ENV variables of the system.

// the third parameter in the main method contains all the env variables.
int main(int argc, char** arg[], char** e){

	int i;
	for(int i=0; e[i]!=NULL;i++){
		printf("%s\n",e[i]);
	}
	return 0;
}
