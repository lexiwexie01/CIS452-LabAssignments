#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit rLim;
    getrlimit(RLIMIT_NPROC, &rLim);
    printf("Maximum number of processes per user (dynamic): %llu", rLim.rlim_max);
}