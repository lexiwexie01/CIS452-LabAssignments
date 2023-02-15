#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

/*
 * The reader will create a key using ftok() on key.txt, just as the writer will do the same.
 * This key will be the same in both programs. This memory will be read from the readers and written in the writer.c.
 * There will be two reader processes that will be reading from shared memory at the same time and
 * will only read if there is new data. We can do this with the variables located in the struct shmid_ds.
 * We can get this data structure by calling shmctl(). This data structure can tell us who last accessed
 * the shared memory.
 * */

int MEM_SIZE = 255;

int sharedMemoryID;

char* sharedMemoryPointer;

void sigHandler(int);

int main() {

    // install interrupt handler
    signal(SIGINT, sigHandler);

    // Get sharedMemoryID of shared memory created by writer.c
    key_t key = ftok(".writer.c", 0);
    sharedMemoryID = shmget(key, MEM_SIZE, S_IWUSR|S_IRUSR|S_IRGRP|S_IWGRP|IPC_CREAT);
    if (sharedMemoryID < 0) {
        perror("Error setting shared memory");
        exit(1);
    }

    // Attach memory
    // TODO: might need a pointer to a char* instead of just char*
    sharedMemoryPointer = shmat(sharedMemoryID, NULL, 0);
    if (sharedMemoryPointer == NULL) {
        perror("Error with attaching shared memory");
        exit(1);
    }

    // Get struct shmid_ds with call to shmctl()
    struct shmid_ds sharedMemoryDataStructure;

    // Create two processes
    pid_t pid;
    for (int i = 0; i < 2; i++) {
        if ((pid = fork()) < 0) {
            perror("Forking process failed");
            exit(1);
        }
        // If child, then exit
        if (pid == 0) {
            break;
        }
    }


    // Main loop for reading processes
    if (pid == 0) {
        char data[MEM_SIZE];
        while (1) {
            // Read memory only if shmid_ds says it was last updated by the creator (writer)
            shmctl(sharedMemoryID, IPC_STAT, &sharedMemoryDataStructure);
            if (sharedMemoryDataStructure.shm_lpid != sharedMemoryDataStructure.shm_cpid) {
                // copy string into data
                strcpy(data, sharedMemoryPointer);
                // display process and new data
                printf("pid: %d data: %s", pid, data);
            }
        }
    }

    // Detach memory
    shmdt(sharedMemoryPointer);
    shmctl(sharedMemoryID, IPC_RMID, sharedMemoryPointer);
    return 0;
}

void sigHandler (int sigNum) {
    // graceful exit
    printf("Closing down processes\n");
    shmdt(sharedMemoryPointer);
    shmctl(sharedMemoryID, IPC_RMID, sharedMemoryPointer);
    exit(0);
}