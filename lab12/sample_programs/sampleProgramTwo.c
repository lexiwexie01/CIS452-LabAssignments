#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    DIR *dirPtr;
    struct dirent *entryPtr;
    struct stat statBuf;

    dirPtr = opendir(".");

    printf("%-*s%-*s\n", 20, "filename", 10, "size (bytes)");
    while ((entryPtr = readdir(dirPtr))) {
        if (stat(entryPtr->d_name, &statBuf) == -1) {
            perror("Program error: ");
            continue;
        }
        printf("%-20s\t%-10lld\n", entryPtr->d_name, statBuf.st_size);
    }

    closedir(dirPtr);
    return 0;
}