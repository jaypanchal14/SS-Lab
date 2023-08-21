#include <stdio.h> 
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd1, fd2, fd3 ,fd4 ,fd5;
	fd1 = open("file1.txt", O_RDWR | O_CREAT);
	fd2 = open("file2.txt", O_RDWR | O_CREAT);
	fd3 = open("file3.txt", O_RDWR | O_CREAT);
    fd4 = open("file4.txt", O_RDWR | O_CREAT);
    fd5 = open("file5.txt", O_RDWR | O_CREAT);
	for(;;);
	//return 0;
}
