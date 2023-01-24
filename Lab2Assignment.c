#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {

    while (1) {
        pid_t pid;
        struct rusage usage_before, usage_after;
        char input[256];
        char* argument_list[256];

        // Get user input
        printf("Enter a string: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        // Parse user input into array
        char* token = strtok(input, " ");
        int argumentListLength = 0;
        while (token != NULL) {
            argument_list[argumentListLength++] = token;
            token = strtok(NULL, " ");
        }

        // Make array NULL terminated
        argument_list[argumentListLength] = NULL;

        // Check for exit condition
        if (strcmp(argument_list[0], "quit") == 0) {
            break;
        }

        // Get usage statistics before
        getrusage(RUSAGE_CHILDREN, &usage_before);

        // Fork and make sure it worked
        if ((pid = fork()) < 0) {
            fprintf(stderr, "Fork failure: %s", strerror(errno));
            exit(1);
        }

        // Handle for the child
        if (pid == 0) {
            // Execute command and check for errors
            int status = execvp(argument_list[0], &argument_list[0]);
            if (status < 0) {
                perror("exec failed");
                exit(1);
            }
        // Handle for the parent
        } else {
            int status;
            waitpid(pid, &status, 0);

            // Ensure child exited properly
            if (WIFEXITED(status)) {

                // Get usage statistics after child process is terminated
                getrusage(RUSAGE_CHILDREN, &usage_after);

                // Calculate the difference between the cpu time values
                struct timeval child_time = {usage_after.ru_utime.tv_sec - usage_before.ru_utime.tv_sec,
                                             usage_after.ru_utime.tv_usec - usage_before.ru_utime.tv_usec};

                // Calculate the difference between the involuntary context switches
                long int nivcsw = usage_after.ru_nivcsw - usage_before.ru_nivcsw;

                // Display statistics
                printf("Child Process %d\n", pid);
                printf("\tCPU time used: %dms\n", child_time.tv_usec);
                printf("\tInvoluntary Context Switches: %ld\n", nivcsw);
            }
        }
    }
    return 0;
}