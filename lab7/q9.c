#include <stdio.h>
#include <sys/resource.h>


int main() {
    struct rlimit rLim;
    getrlimit(RLIMIT_NOFILE, &rLim);
    printf("Maximum number of open files, hard limit (dynamic): %llu", rLim.rlim_max);
}