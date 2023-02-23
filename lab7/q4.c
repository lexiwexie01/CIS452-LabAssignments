#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main() {
    int c = 1;
    while (1) {
        int sharedMemoryID = shmget(IPC_PRIVATE, c, IPC_CREAT | S_IRUSR | S_IWUSR);
        if (sharedMemoryID < 0) {
            printf("Maximum value of a shared memory segment (empirical): %d", c);
            exit(0);
        }
        // Remove shared memory
        if(shmctl(sharedMemoryID, IPC_RMID, 0) < 0) {
            perror ("Unable to deallocate");
            exit(1);
        }
        c++;
    }
}