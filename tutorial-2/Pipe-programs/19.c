#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
Objective: Create a FIFO file.
*/

void main(){

    /*
    (a) mknod command:
    mknod <name> <type>   i.e., mknod a p
    <name> : your desired name
    <type> -> p: pipe,  c: character device, b: block device
    */

    /*
    (b) mkfifo command:
    mkfifo <name>
    */
    
    /*
    (c)use strace command to find out, which command (mknod or mkfifo) is better.
    Run these two commands:
    strace mknod a p
    strace mkfifo a
    -> By analyzing, we can say mkfifo is better for creating pipe.
    */

    //(d) Using mknod system call
    if(mknod("ff", S_IFIFO | 0744, 0)){
        perror("Failure while creating fifo 'ff'");
        exit(1);
    }

    //(e) Using mkfifo system call
    if(mkfifo("ff" , 0744)){
        perror("Failure while creating fifo 'ff'");
        exit(1);
    }
    return 0;

}