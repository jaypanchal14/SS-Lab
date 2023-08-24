#include <stdio.h>

// the third parameter in the main method contains all the env variables.
int main(int argc, char** arg[], char** e){

	int i;
	for(int i=0; e[i]!=NULL;i++){
		printf("%s\n",e[i]);
	}
	return 0;
}
