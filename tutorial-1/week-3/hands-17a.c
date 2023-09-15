#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//Objective : to demonstrate the file-locking under hands-17b.c program,
//			  this program will create a sample file.

int main()
{
	printf("Enter an initial ticket-count which will be stored in 'ticket.txt'\n");
	int c;
	scanf("%d",&c);
	printf("Initial ticket number: %d\n",c);
	int fd = open("ticket.txt", O_CREAT | O_RDWR, 0644);
	
	//1)Writing with struct
	//struct{int no;} ticket;
	//ticket.no = c;
	//write(fd, &ticket, sizeof(ticket));
	
	//2)writing with int directly
	write(fd, &c, sizeof(c));
	close(fd);
	return 0;
}
