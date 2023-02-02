#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fputs("Usage: must supply a command\n", stderr);
		exit(1);
	}

	puts("Before the exec");
	if (execvp(argv[1], &argv[1]) < 0) {
		perror("exec failed");
		exit(1);
	}
	puts("After the exec");

	return 0;
}
