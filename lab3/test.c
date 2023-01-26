#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < 5; i++) {
        int t = rand() % 5 + 1;
        sleep(t);
        printf("time:%d\n", t);
    }
    return 0;
}