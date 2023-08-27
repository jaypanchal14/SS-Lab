#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	
	int fd = open("3-records.txt", O_RDWR | O_CREAT, 0644);
	if(fd == -1){
		printf("Not able to open the file");
	}else{
		printf("Enter three different integers separated by a single space");
		int a,b,c;
		scanf("%d %d %d", &a, &b, &c);
		write(fd, &a, sizeof(a));
		write(fd, &b, sizeof(b));
		write(fd, &c, sizeof(c));
		close(fd);
	}
	return 0;
}
