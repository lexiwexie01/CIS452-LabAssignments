#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

struct myStruct {
    int num;
    char str[40];
};

int main() {

    // Create shared memory
    key_t key = ftok("./ic7-producer.c", 0);
    int sharedMemoryID = shmget(key, sizeof(struct myStruct), S_IWUSR|S_IRUSR|S_IRGRP|S_IWGRP|IPC_CREAT);
    if (sharedMemoryID < 0) {
        perror("Error setting shared memory");
        exit(1);
    }

    // Attach memory
    struct myStruct* sharedMemoryPointer = shmat(sharedMemoryID, NULL, 0);
    if (sharedMemoryPointer == NULL) {
        perror("Error with attaching shared memory");
        exit(1);
    }

    // Change memory
    sharedMemoryPointer->num = 42;
    strcpy(sharedMemoryPointer->str, "Not Hello World");

    // Detach memory
    shmdt(sharedMemoryPointer);

}