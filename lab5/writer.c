#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

/*
 * The writer will create the shared memory segment using schmget and IPC_CREATE,
 * and then it will accept user input from the terminal and write it into the
 * shared memory segment it created.
 */

int MEM_SIZE = 255;

int sharedMemoryID;
char* sharedMemoryPointer;

int main() {
    // Create shared memory
    key_t key = ftok(".writer.c", 0);
    sharedMemoryID = shmget(key, MEM_SIZE, S_IWUSR|S_IRUSR|S_IRGRP|S_IWGRP|IPC_CREAT);
    if (sharedMemoryID < 0) {
        perror("Error setting shared memory");
        exit(1);
    }

    // Attach memory
    sharedMemoryPointer = shmat(sharedMemoryID, NULL, 0);
    if (sharedMemoryPointer == NULL) {
        perror("Error with attaching shared memory");
        exit(1);
    }
    while (1) {
        // Listen for user input
        while (1) {
            // Check to make sure writer has written output
            // Write to shared memory
        }

    }

    // Detach memory
    shmdt(sharedMemoryPointer);
    return 0;
}

void sigHandler(int sigNum) {
    printf("Closing down processes\n");
    shmdt(sharedMemoryPointer);
    shmctl(sharedMemoryID, IPC_RMID, sharedMemoryPointer);
    exit(0);
}