#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
    if ((key = ftok("/tmp", 'A')) == -1) {
        perror("Error while generating key");
        exit(1);
    }
    int shm_id;
    char *addr;
    char data[] = "This is the data to be written to shared memory";

    // Create a shared memory segment with a specified key and permissions
    // size: 1024 bytes
    if ((shm_id = shmget(key, 1024, IPC_CREAT | 0666)) == -1) {
        perror("Error while creating memory segment");
        exit(1);
    }

    // Attach to the shared memory segment for writing
    addr = shmat(shm_id, NULL, 0);
    if (addr == (char *)(-1)) {
        perror("Error while attaching memory segment");
        exit(1);
    }

    // Write data to shared memory
    strcpy(addr, data);

    printf("Data written to shared memory: %s\n", addr);

    // Updating with read-only access
    addr = shmat(shm_id, NULL, SHM_RDONLY);
    if (shmaddr == (char *)(-1)) {
        perror("Error while updating mode");
    }

    // Write data to shared memory, it will fail
    strcpy(addr, data);
  
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
