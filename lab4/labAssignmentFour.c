#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <stdbool.h>
#include <time.h>

void* getFile(void*);

void sigHandler(int);

int totalFileRequests;

int main() {
    signal (SIGINT, sigHandler);
    totalFileRequests = 0;

    do {
        // Wait for user input
        char input[63];
        printf("Enter a file name:\n");
        fgets(input, sizeof(input), stdin);

        // Create new thread with user input as param
        pthread_t thread;
        int threadStatus = pthread_create(&thread, NULL, getFile, &input);
        if (threadStatus != 0) {
            fprintf(stderr, "Thread create error %d: %s\n", threadStatus, strerror(threadStatus));
            exit(1);
        }

        // Increment total thread count
        totalFileRequests++;

    } while(1);
}

void* getFile(void* myArgument) {
    // Create a copy of the file being accessed
    char *filename = malloc(sizeof(char)*100);
    strcpy(filename, (char*)myArgument);

    // Seed random with current time
    srand(time(NULL));

    // false for 20%, true for 80%
    bool prob = (rand() % 5) ? true : false;

    if (prob) {
        sleep(1);
    } else {
        sleep((rand() % 4) + 7);
    }

    // print diagnostic message
    printf("File accessed: %s\n", filename);
    return NULL;
}

void sigHandler (int sigNum){
    // graceful exit
    printf("Total File Requests Received: %d\n", totalFileRequests);
    exit(0);
}