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

struct termios termios;

int totalFileRequests;

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("Fork failure");
        exit(1);
    }

    if (pid == 0) {
        char* tmp[] = {"stty", "-echoctl", NULL};
        int status = execvp(tmp[0], tmp);
        if (status < 0) {
            perror("exec failed");
            exit(1);
        }
        exit(0);
    }

    signal (SIGINT, sigHandler);
    totalFileRequests = 0;

    do {
        // Wait for user input
        char input[63];
        printf("Enter a file name: ");
        fgets(input, sizeof(input), stdin);

        // Create new thread with user input as param
        // TODO: might kill the thread when we loop. If so, could create a queue
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
    char *myPtr = (char *)myArgument;
    srand(time(NULL));

    // false for 20%, true for 80%
    bool prob = (rand() % 5) ? true : false;

    if (prob) {
        sleep(1);
    } else {
        sleep((rand() % 4) + 7);
    }

    // print diagnostic message
    printf("File accessed: %s\n", myPtr);
    return NULL;
}

void sigHandler (int sigNum){
    // graceful exit
    printf("Total File Requests Received: %d", totalFileRequests);
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("Fork failure");
        exit(1);
    }

    if (pid == 0) {
        char* tmp[] = {"stty", "echoctl", "ON", NULL};
        int status = execvp(tmp[0], tmp);
        if (status < 0) {
            perror("exec failed");
            exit(1);
        }
        exit(0);
    }
    exit(0);
}