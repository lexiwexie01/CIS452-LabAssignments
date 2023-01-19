#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int running = 1;

    while (running) {
        pid_t pid, child;
        int status;

        char in1[100];
        printf("Please enter a command: ");
        fgets(in1, 100, stdin);
        printf("input: %s\n", in1);
        char in2[100];
        strcpy(in2, in1);

        char* tk1;
        int c = 0;
        tk1 = strtok(in1, " ");
        while (tk1 != NULL) {
            c++;
//            printf("%s\n", tk1);
            tk1 = strtok(NULL, " ");
        }

        char* argument_list[c];
        char* tk2;
        tk2 = strtok(in2, " ");
        for (int i = 0; tk2 != NULL; i++) {
            strcpy(argument_list[i], tk2);
//            printf("%s\n", tk2);
            tk2 = strtok(NULL, " ");
        }

        printf("size: %d\n", c);
        for (int j = 0; j < c; j++) {
            printf("%s\n", argument_list[j]);
        }

//        if ((pid = fork()) < 0) {
//            fprintf(stderr, "Fork failure: %s", strerror(errno));
//            exit(1);
//        } else if (pid == 0) {
//            if (execvp(argument_list[0], &argument_list[0]) < 0) {
//                perror("exec failed");
//                exit(1);
//            }
//        } else {
//            child = wait(&status);
//            status = WEXITSTATUS(status);
//            printf("Child PID: %ld terminated with return status %d\n", (long) child, status);
//        }
    }
}

/*
    while running
        get user input
        if input == exit
                running = 0
        if ((pid = fork) < 0)
            There was an issue
        if (pid == 1)
            We are a child
            use execvp() to call terminal
            If execvp didn't work
                print stuff and exit with bad code
        else
            wait()
            use some resource statistics stuff to get info from child's process
            print that out
    return 0
*/