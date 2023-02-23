#include <stdio.h>
#include <unistd.h>


int main() {
    printf("Page size in bytes (dynamic): %d", getpagesize());
}