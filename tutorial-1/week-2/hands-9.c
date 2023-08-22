#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* arg[]){
	
	if(argc!=2){
		printf("Only single file-name needs to be passed along with the executable file command.\n");
		return 0;
	}
	struct stat buf;
	int result = stat(arg[1], &buf);
	if(result<0){
		printf("Error in getting stat of file\n");
		return 0;	
	}
	printf("Information about file : %s\n",arg[1]);
	printf("Inode : %ld \n", buf.st_ino);
	printf("Number of hard-links : %ld \n", buf.st_nlink);
	printf("User-Id : %d \n", buf.st_uid);
	printf("Group-Id : %d \n", buf.st_gid);
	printf("Size : %ld \n", buf.st_size);
	printf("Block-size : %ld \n", buf.st_blksize);
	printf("Number of blocks : %ld \n", buf.st_blocks);
	printf("Time of last access : %ld \n", buf.st_atim);
	printf("Time of last modification : %ld \n", buf.st_mtim);
	printf("Time of last change : %ld \n", buf.st_ctim);
	return 0;
}
