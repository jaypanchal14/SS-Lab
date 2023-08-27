#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	
	int fd = open("ticket.txt", O_RDWR, 0644);
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	
	printf("Before entering the critical section\n");
	int got_lock = fcntl(fd, F_SETLKW, &lock);
	if(got_lock == -1){
		printf("Unable to get the lock.\n");
	}else{
		printf("Got the lock, in critical section.\n");
	}
	
	int ticket_no;
	int read_done = read(fd, &ticket_no, sizeof(ticket_no));
	if(read_done != -1){
		printf("New ticket number after updating: %d\n",++ticket_no);		
	}else{
		printf("Not able to read from the file\n");
	}
	
	//To bring it back to starting of file to write back at correct location.
	lseek(fd, 0, SEEK_SET);
	int write_done = write(fd, &ticket_no, sizeof(ticket_no));
	if(write_done == -1){
		printf("Not able to update the ticket-count in 'ticket.txt' file.\n");
	}else{
		printf("Ticket-count updated in 'ticket.txt' file.\n");
	}
	
	printf("Enter any character to unlock the file");
	getchar();
	lock.l_type = F_UNLCK;
	got_lock = fcntl(fd, F_SETLKW, &lock);
	if(got_lock == -1){
		printf("Unable to release the lock over the file.\n");
	}else{
		printf("Exited critical section.\n");
	}
	close(fd);
	return 0;
}
