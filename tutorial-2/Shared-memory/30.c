#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*
Objective:
Write a program to create a shared memory.
(a) write some data to the shared memory
(b) attach with O_RDONLY and check whether you are able to overwrite.
(c) detach the shared memory
(d) remove the shared memory
*/

int main() {
    
    int key;
    // Getting unique key for the message queue
    if ((key = ftok("/tmp", 'C')) == -1) {
        perror("Error while generating key");
        exit(1);
    }
    int shm_id;

    // Create a shared memory segment with a specified key and permissions
    // size: 1024 bytes
    if ((shm_id = shmget(key, 1024, IPC_CREAT | 0777)) == -1) {
        perror("Error while creating memory segment");
        exit(1);
    }

    // Attach to the shared memory segment for writing
    char* addr = (char*)shmat(shm_id, NULL, 0);
    if (addr == (void *)-1) {
        perror("Error while attaching memory segment");
        exit(1);
    }
    char data[] = "This is the data to be written to shared memory";

    // Write data to shared memory
    strcpy(addr, data);

    printf("Data written to shared memory: %s\n", addr);
    //Need to detach from the memory in order to update the flag
    if(shmdt(addr) == -1) {
            perror("Error while detaching from segment before updating the mode");
    }

    // Updating with read-only access
    addr = (char *)shmat(shm_id, NULL, SHM_RDONLY);
    
    if (addr == (void *)-1) {
        perror("Error while updating mode");
    }

    // Write data to shared memory, it will fail and give segmentation fault
    //strcpy(addr, "Going to fail");

    /*int pId = fork();
    
    if(pId == 0){
        //Child process
        // Write data to shared memory, it will fail and give segmentation fault
        printf("Inside child process before writing: %s\n",addr);
        strcpy(addr, "Going to fail");
        printf("Inside child process: %s\n",addr);
        exit(1);
    }
    
    sleep(2);
    printf("Before parent process: %s\n",addr);
    strcpy(addr, "Going to fail");
    printf("After parent process: %s\n",addr);*/

    // Detach the shared memory segment
    if(shmdt(addr) == -1) {
            perror("Error while detaching from segment");
    }
  
    // Remove the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("Error while deleting memory segment");
        exit(1);
    }

    printf("Shared memory deleted.\n");

    return 0;
}
