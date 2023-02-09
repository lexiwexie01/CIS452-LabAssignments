#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

/*
 * The reader will create a key using ftok() on key.txt, just as the writer will do the same.
 * This key will be the same in both programs. We can then use shmget() in one of the programs to
 * create the shared memory. This memory will be read from the readers and written in the writer.c.
 * There will be two reader processes that will be reading from shared memory at the same time and
 * will only read if there is new data. We can do this with the variables located in the struct shmid_ds.
 * We can get this data structure by calling shmctl(). This data structure can tell us who last accessed
 * the shared memory.
 * */

int main(int argc, char* argv[]) {
    printf("Hello, World!");
}