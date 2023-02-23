#include <stdio.h>
#include <unistd.h>


int main() {
    printf("Maximum number of semaphores per process (static): %d", _SC_SEM_NSEMS_MAX);
}