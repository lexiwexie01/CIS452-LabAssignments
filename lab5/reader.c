#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

/*
 * The reader will create a key using ftok() on key.txt, just as the writer will do the same.
 * This key will be the same in both programs. This memory will be read from the readers and written in the writer.c.
 * There will be two reader processes that will be reading from shared memory at the same time and
 * will only read if there is new data. We can do this with the variables located in the struct shmid_ds.
 * We can get this data structure by calling shmctl(). This data structure can tell us who last accessed
 * the shared memory.
 * */

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

    printf("ppid: %d\n\n", getpid());

    // Create two processes
    pid_t pid;
    for (int i = 0; i < 2; i++) {
        if ((pid = fork()) < 0) {
            perror("Forking process failed");
            sigHandler(100);
        }
        // If child, then exit
        if (pid == 0) {
            break;
        }
    }


    // Main loop for reading processes
    if (pid == 0) {

        // Display process' id
        pid = getpid();
        printf("pid: %d\n", pid);

        // Get sharedMemoryID of shared memory created by writer.c
        key_t key = ftok("key.txt", 1);
        if (key < 0) {
            perror("Failed creating key");
            exit(1);
        }

        printf("key: %d\n", key);

        sharedMemoryID = shmget(key, sizeof(struct memStruct), SHM_RDONLY);
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
        }

        printf("shmptr: %p\n", sharedMemoryPointer);

        // Get struct shmid_ds with call to shmctl()
        struct shmid_ds* sharedMemoryDataStructure = malloc(sizeof(struct shmid_ds*));
        if (sharedMemoryDataStructure == NULL) {
            perror("Error with creating shared memory id data structure");
            sigHandler(100);
        }

        if (shmctl(sharedMemoryID, IPC_STAT, sharedMemoryDataStructure) < 0) {
            perror("Unable to access shared memory data structure");
            sigHandler(100);
            exit(1);
        }

        printf("cpid: %d\n", sharedMemoryDataStructure->shm_cpid);
        printf("lpid: %d\n\n", sharedMemoryDataStructure->shm_lpid);

        while (1) {
            // Read memory only if shmid_ds says it was last updated by the creator (writer)
            if (shmctl(sharedMemoryID, IPC_STAT, sharedMemoryDataStructure) < 0) {
                perror("Unable to access shared memory data structure");
                sigHandler(100);
                exit(1);
            }

            if (sharedMemoryDataStructure->shm_lpid == sharedMemoryDataStructure->shm_cpid) {
                // copy string into data
                char data[MEM_SIZE];
                strcpy(data, sharedMemoryPointer->data);
                // display process and new data
                printf("read from shared memory:\n");
                printf("\tshm: %s\n", sharedMemoryPointer->data);
                printf("\tlpid: %d\n", sharedMemoryDataStructure->shm_lpid);
                printf("\tpid: %d\n", pid);
                printf("\tdata: %s", data);
            }
        }
    } else {
        int stats;
        wait(&stats);
        printf("Closing down processes\n");
        if(shmdt (sharedMemoryPointer) < 0) {
            perror ("Unable to detach shared memory\n");
            sigHandler(100);
        }
        if(shmctl (sharedMemoryID, IPC_RMID, 0) < 0) {
            perror ("Unable to deallocate shared memory\n");
            sigHandler(100);
        }
        exit(0);
    }
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