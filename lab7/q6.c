#include <stdio.h>
#include <unistd.h>


int main() {
    printf("Number of physical pages in a system (dynamic): %d", _SC_PHYS_PAGES);
}