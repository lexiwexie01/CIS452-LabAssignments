#include <stdio.h>
#include <sys/resource.h>


int main() {
    struct rlimit rLim;
    getrlimit(RLIMIT_FSIZE, &rLim);
    printf("Maximum filesize in bytes (dynamic): %llu", rLim.rlim_max);
}