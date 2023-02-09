#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define FOO 4096

int main ()
{
    int shmId;
    char *sharedMemoryPtr;
    if((shmId = shmget(IPC_PRIVATE, FOO, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) {
        perror ("Unable to get shared memory\n");
        exit (1);
    }
    if((sharedMemoryPtr = shmat (shmId, 0, 0)) == (void*) -1) {
        perror ("Unable to attach\n");
        exit (1);
    }
    printf("Shared Memory Segment ID: %d\nValue a: %p\t Value b: %p\n", shmId, (void *) sharedMemoryPtr, (void *) sharedMemoryPtr + FOO);
    pause();
    struct shmid_ds shmDataStruct;
    if (shmctl(shmId, IPC_STAT, &shmDataStruct) < 0) {
        perror("Unable to get shmid_ds");
        exit(1);
    }
    printf("Memory Segment Size: %zu\n", shmDataStruct.shm_segsz);
    if(shmdt (sharedMemoryPtr) < 0) {
        perror ("Unable to detach\n");
        exit (1);
    }
    if(shmctl (shmId, IPC_RMID, 0) < 0) {
        perror ("Unable to deallocate\n");
        exit(1);
    }
    return 0;
}