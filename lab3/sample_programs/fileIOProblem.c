#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int fd = open("temp.txt", O_RDWR);
	if (fd < 0) {
		perror("file read error");
		return 1;
	}

	char* command[] = {"ls", "-l", NULL};

	// This will redirect anything from stdout to test.txt
	// That means that if we print anything, it'll go to 
	// test.txt
	dup2(fd, 1);

	pid_t pid = fork();
	if (pid < 0) {
		perror("fork error");
	}

	if (pid == 0) {
		// This is the child
		if (execvp(command[0], &command[0]) < 0) {
			perror("exec failed");
			exit(1);
		}
	} else {
		// This is the parent
		int status;
        waitpid(pid, &status, 0);
        return 0;
	}

	return 0;
}