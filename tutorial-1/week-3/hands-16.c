#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** arg){
	
	if(argc!=2){
		printf("Need to pass one file-name with executable file.\n");
	}
	
	//These program will perform mandatory file locking
	//Kernel will only one file to access the file who has acquired lock over it,
	//Other process can't access the same file until the lock is released.
	
	//permission will be applied to the file, only when new file is created.
	int fd = open(arg[1], O_CREAT | O_RDWR, 0644);
	
	//Objective :
	//1) Obtain write-lock
	//2) Release write-lock
	//3) Obtain read-lock
	//4) Release read-lock
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0; // Lock entire file
	lock.l_pid = getpid();
	
	printf("Before entering the critical section with write lock.\n");
	//This will wait till the lock is obtained
	int gotLock = fcntl(fd, F_SETLKW, &lock);
	if(gotLock==-1){
		printf("Got error while acquiring lock on the file.\n");
	}else{
		printf("Got the write lock on the file.\n");
	}
	printf("Enter any character to release the lock");
	getchar();
	
	lock.l_type = F_UNLCK;
	gotLock = fcntl(fd, F_SETLK, &lock);
	printf("Exiting from the critical section(Write lock released)\n");
	
	sleep(5);
	
	printf("Before entering the critical section with read lock.\n");
	//This will wait till the lock is obtained
	lock.l_type = F_RDLCK;
	gotLock = fcntl(fd, F_SETLKW, &lock);
	if(gotLock==-1){
		printf("Got error while acquiring lock on the file.\n");
	}else{
		printf("Got the read lock on the file\n");
	}
	printf("Enter any character to release the lock");
	getchar();
	
	lock.l_type = F_UNLCK;
	gotLock = fcntl(fd, F_SETLK, &lock);
	printf("Exiting from the critical section(Read lock released)\n");
	
	close(fd);
	
	return 0;
}
