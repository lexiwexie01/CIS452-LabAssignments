#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

/*
 * The writer will create the shared memory segment using schmget and IPC_CREATE,
 * and then it will accept user input from the terminal and write it into the
 * shared memory segment it created.
 */

int main(int argc, char* argv[]) {
    return 0;
}