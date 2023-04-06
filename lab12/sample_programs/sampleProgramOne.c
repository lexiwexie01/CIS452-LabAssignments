#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    struct stat statBuf;

    if (argc < 2) {
        printf("Usage: argument (filename) expected\n");
        exit(1);
    }

    if (stat (argv[1], &statBuf) < 0) {
        perror("Program error: ");
        exit(1);
    }

    printf("Is Directory: %d\n", S_ISDIR(statBuf.st_mode));

    printf("inode value is : %llu\n", statBuf.st_ino);

    return 0;
}
