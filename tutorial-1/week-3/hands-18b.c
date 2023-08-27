#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	
	int fd = open("3-records.txt", O_RDWR, 0644);
	
	int a,b,c;
	if(fd == -1){
		printf("Not able to open the records file.\n");
		return 0;
	}else{
		read(fd, &a, sizeof(a));
		read(fd, &b, sizeof(b));
		read(fd, &c, sizeof(c));
		printf("Current values of records:\n1)a: %d\n2)b: %d\n3)c: %d\n",a,b,c);
		
	}
	printf("Select record number (either 1 or 2 or 3): \n");
	int record, start;
	scanf("%d",&record);
	fflush(stdin);
	fflush(stdout);
	if(record == 1 || record == 2 || record == 3){
		start = (record-1)*sizeof(record);
	}
	else{
		printf("Not valid record number\n");
		return 0;
	}
	
	lseek(fd, start, SEEK_SET);
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = start;
	lock.l_len = sizeof(int);
	lock.l_pid = getpid();
	
	printf("Before entering the critical section.\n");
	int gotLock = fcntl(fd, F_SETLKW, &lock);
	if(gotLock == -1){
		printf("Unable to get the lock.\n");
	}else{
		printf("Got the lock, in critical section.\n");
	}
	
	int value;
	int op_done = read(fd, &value, sizeof(value));
	if(op_done != -1){
		printf("New value to be updated for record %d is : %d\n", record,++value);		
	}else{
		printf("Not able to read from the file\n");
	}
	lseek(fd, start, SEEK_SET);
	op_done = write(fd, &value, sizeof(value));
	if(op_done == -1){
		printf("Not able to update the record-value in file.\n");
	}else{
		printf("Record-value is now updated in the file.\n");
	}
	
	printf("Enter any character to unlock the record\n");
	//Putting below getchar() twice as it is taking '\n' character from previous lines
	//Adding fflush(stdin) was not removing the line-feed from the stdin.
	getchar();getchar();
	lock.l_type = F_UNLCK;
	gotLock = fcntl(fd, F_SETLKW, &lock);
	if(gotLock == -1){
		printf("Unable to release the lock over the record.\n");
	}else{
		printf("Exited critical section.\n");
	}
	
	close(fd);
	return 0;
}
