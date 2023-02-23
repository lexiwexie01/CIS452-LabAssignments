#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/sem.h>


int main() {
    int c = 0;
    while (1) {
        int semaphoreID = semget(IPC_PRIVATE, 1, SEM_A|SEM_R);
        if (semaphoreID < 0) {
            printf("Maximum value of a counting semaphore (empirical): %d", c);
            exit(0);
        }
        c++;
    }
}