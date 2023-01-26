#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define READ 0
#define WRITE 1

void sigHandler (int);

int main() {
    int fd[2];
    int pipeCreationResult;
    int childPID;

    // Create a pipe between the parent and child
    pipeCreationResult = pipe(fd);

    // Ensure pipe was created properly
    if(pipeCreationResult < 0) {
        perror("Failed pipe creation\n");
        exit(1);
    }

    // Fork a child and ensure fork was executed properly
    childPID = fork();
    if(childPID < 0) { // Fork failed
        perror("Fork failed");
        exit(1);
    }

    if(childPID == 0) { // Child process
        close(fd[0]);
        int sigNum, t;

        while (1) {
            // Wait a random amount of time between 1 and 5 seconds
            t = rand() % 5 + 1;
            sleep(t);

            // Set the signal to be sent
            if (rand() % 2) {
                sigNum = SIGUSR1;
            } else {
                sigNum = SIGUSR2;
            }

            // Send the signal to the parent
            write(fd[1], &sigNum, sizeof(int));
        }
    } else { // Parent process
        // Define what signals call the sigHandler() function
        signal(SIGINT, sigHandler);
        signal(SIGUSR1, sigHandler);
        signal(SIGUSR2, sigHandler);

        close(fd[1]);
        printf("Spawned child PID#%d\n", childPID);
        int sigNum;
        while (1) {
            printf("waiting... \t\t");

            // Read the signal from the child
            read(fd[0], &sigNum, sizeof(int));

            // Send the signal to this process
            kill(getpid(), sigNum);
        }
    }
    return 0;
}

void sigHandler(int sigNum) {
    // Handle signals indicated by sigNum
    switch (sigNum) {
        case SIGUSR1:
            printf("received a SIGUSR1 signal\n");
            break;
        case SIGUSR2:
            printf("received a SIGUSR2 signal\n");
            break;
        case SIGINT:
            // Handle the interrupt signal by closing the child and parent
            printf("^C received. That's it, I'm shutting you down...\n");
            exit(0);
    }
}


