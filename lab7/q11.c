#include <stdio.h>
#include <time.h>

int main() {
    struct timespec res;
    clock_getres(CLOCK_REALTIME, &res);
    printf("Clock resolution in milliseconds (dynamic): %ld", res.tv_nsec);
}