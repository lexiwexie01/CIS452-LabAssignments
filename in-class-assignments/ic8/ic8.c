#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/wait.h>

#define SIZE 16


int semaphoreID;
int sharedMemoryID;
long int *sharedMemoryPointer;

void sigHandler(int);

int main(int argc, char *argv[]) {

    signal(SIGINT, sigHandler);

    int status;
    long int i, loop, temp;
    struct sembuf sem_lock = {0, -1, SEM_UNDO};
    struct sembuf sem_unlock = {0, 1, SEM_UNDO};
    pid_t pid;
    loop = atoi(argv[1]);

    // Create shared memory
    sharedMemoryID = shmget(IPC_PRIVATE, SIZE, IPC_CREAT|S_IRUSR|S_IWUSR);
    if(sharedMemoryID < 0) {
        perror ("Unable to obtain shared memory\n");
        exit (1);
    }

    // Get pointer to shared memory
    sharedMemoryPointer = shmat(sharedMemoryID, 0, 0);
    if(sharedMemoryPointer == (void*) -1) {
        perror ("Unable to attach");
        exit (1);
    }

    // Set starting values at shared memory location
    sharedMemoryPointer[0] = 0;
    sharedMemoryPointer[1] = 1;

    // Create semaphore
    semaphoreID = semget(IPC_PRIVATE, 1, S_IRUSR);
    if (semaphoreID < 0) {
        perror("Unable to create semaphore");
        exit(1);
    }

    // Initialize semaphore
    if (semctl(semaphoreID, 0, SETVAL, 1) < 0) {
        perror("Unable to initialize semaphore");
        exit(1);
    }

    // Fork child process
    pid = fork();
    if(pid < 0){
        printf("Fork failed");
    }

    if(pid == 0) { // Child
        for(i=0; i < loop; i++) {

            // Lock semaphore
            if (semop(semaphoreID, &sem_lock, 1) < 0) {
                perror("Unable to lock semaphore");
                exit(1);
            }

            // swap the contents of sharedMemoryPointer[0] and sharedMemoryPointer[1]
            temp = sharedMemoryPointer[0];
            sharedMemoryPointer[0] = sharedMemoryPointer[1];
            sharedMemoryPointer[1] = temp;

            // Unlock semaphore
            if (semop(semaphoreID, &sem_unlock, 1) < 0) {
                perror("Unable to unlock semaphore");
                exit(1);
            }
        }
        if(shmdt(sharedMemoryPointer) < 0) {
            perror ("Unable to detach");
            exit (1);
        }
        exit(0);
    } else {
        for (i = 0; i < loop; i++) {

            // Lock semaphore
            if (semop(semaphoreID, &sem_lock, 1) < 0) {
                perror("Unable to lock semaphore");
                exit(1);
            }

            // swap the contents of sharedMemoryPointer[1] and sharedMemoryPointer[0]
            temp = sharedMemoryPointer[1];
            sharedMemoryPointer[1] = sharedMemoryPointer[0];
            sharedMemoryPointer[0] = temp;

            // Unlock semaphore
            if (semop(semaphoreID, &sem_unlock, 1) < 0) {
                perror("Unable to unlock semaphore");
                exit(1);
            }
        }
    }

    wait(&status);

    // Print final values
    printf("Values: %li\t%li\n", sharedMemoryPointer[0], sharedMemoryPointer[1]);

    // Detach from shared memory
    if(shmdt(sharedMemoryPointer) < 0) {
        perror ("Unable to detach");
        exit (1);
    }

    // Delete semaphore
    if (semctl(semaphoreID, 0, IPC_RMID) == -1) {
        perror("Unable to delete semaphore");
        exit(1);
    }

    // Remove shared memory
    if(shmctl(sharedMemoryID, IPC_RMID, 0) < 0) {
        perror ("Unable to deallocate");
        exit(1);
    }

    return 0;
}

void sigHandler(int sigNum) {
    // Detach from shared memory
    if(shmdt(sharedMemoryPointer) < 0) {
        perror ("Unable to detach");
        exit (1);
    }

    // Delete semaphore
    if (semctl(semaphoreID, 0, IPC_RMID) == -1) {
        perror("Unable to delete semaphore");
        exit(1);
    }

    // Remove shared memory
    if(shmctl(sharedMemoryID, IPC_RMID, 0) < 0) {
        perror ("Unable to deallocate");
        exit(1);
    }
}