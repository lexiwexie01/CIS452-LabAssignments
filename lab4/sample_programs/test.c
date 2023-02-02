#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {

    srand(time(NULL));
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    for(int i = 0; i < 1000000; i++) {
        int val = (rand() % 4) + 7;
        if (val == 7) {
            a++;
        } else if (val == 8) {
            b++;
        } else if (val == 9) {
            c++;
        } else if (val == 10) {
            d++;
        } else {
            printf("oop\n");
        }

    }
    printf("a: %d\tb: %d\tc: %d\td: %d\n", a, b, c, d);
}