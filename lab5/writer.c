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

struct memStruct {
    char data[255];
};

int sharedMemoryID;

struct memStruct* sharedMemoryPointer;

void sigHandler(int);

int main() {

    // install interrupt handlers
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);

    pid_t pid = getpid();
    printf("pid: %d\n", getpid());

    // Create shared memory
    key_t key = ftok("key.txt", 1);
    if (key < 0) {
        perror("Failed creating key");
        exit(1);
    }

    printf("key: %d\n", key);

    sharedMemoryID = shmget(key, sizeof(struct memStruct), S_IWUSR|S_IRUSR|S_IRGRP|S_IWGRP|IPC_CREAT);
    if (sharedMemoryID < 0) {
        perror("Error setting shared memory");
        exit(1);
    }

    printf("shmid: %d\n", sharedMemoryID);

    // Attach memory
    sharedMemoryPointer = shmat(sharedMemoryID, 0, 0);
    if (sharedMemoryPointer < 0) {
        perror("Error with attaching shared memory");
        sigHandler(100);
        exit(1);
    }

    printf("shmptr: %p\n", sharedMemoryPointer);

    struct shmid_ds* sharedMemoryDataStructure = malloc(sizeof(struct shmid_ds*));
    if (sharedMemoryDataStructure == NULL) {
        perror("Error with creating shared memory id data structure");
        sigHandler(100);
        exit(1);
    }

    // Listen for user input
    char input[MEM_SIZE];
    fgets(input, MEM_SIZE, stdin);
    strcpy(sharedMemoryPointer->data, input);
    if (shmctl(sharedMemoryID, IPC_STAT, sharedMemoryDataStructure) < 0) {
        perror("Unable to access shared memory data structure");
        sigHandler(100);
        exit(1);
    }
    printf("written to shared memory:\n");
    printf("\tshm: %s\n", sharedMemoryPointer->data);
    printf("\tlpid: %d\n", sharedMemoryDataStructure->shm_lpid);
    printf("\tpid: %d\n", pid);

    while (1) {
        while (1) {
            // Check to make sure reader has read the output
            if (shmctl(sharedMemoryID, IPC_STAT, sharedMemoryDataStructure) < 0) {
                perror("Unable to access shared memory data structure");
                sigHandler(100);
                exit(1);
            }
//            printf("lpid: %d", sharedMemoryDataStructure->shm_lpid);
            if (sharedMemoryDataStructure->shm_lpid != pid) {
                // copy input into shared memory
                strcpy(sharedMemoryPointer->data, input);
                printf("written to shared memory:\n");
                printf("\tshm: %s\n", sharedMemoryPointer->data);
                printf("\tlpid: %d\n", sharedMemoryDataStructure->shm_lpid);
                printf("\tpid: %d\n", pid);
                break;
            }
        }
        fgets(input, MEM_SIZE, stdin);
    }

    printf("Closing down processes\n");
    if(shmdt (sharedMemoryPointer) < 0) {
        perror ("Unable to detach shared memory\n");
        exit (1);
    }
    if(shmctl (sharedMemoryID, IPC_RMID, 0) < 0) {
        perror ("Unable to deallocate shared memory\n");
        exit(1);
    }
    exit(0);
}

void sigHandler(int sigNum) {
    // graceful exit
    printf("Closing down processes\n");
    if(shmdt (sharedMemoryPointer) < 0) {
        perror ("Unable to detach shared memory\n");
        exit (1);
    }
    if(shmctl (sharedMemoryID, IPC_RMID, 0) < 0) {
        perror ("Unable to deallocate shared memory\n");
        exit(1);
    }
    // Calling code had an error
    if (sigNum == 100) {
        exit(1);
    } else {
        exit(0);
    }
}