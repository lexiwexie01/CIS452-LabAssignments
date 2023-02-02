#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int i, limit;
	if (argc < 2) {
		fprintf(stderr, "Usage: must supply a limit value\n");
		exit(1);
	}
	limit = atoi(argv[1]);
	sleep(10);
	fork();
	sleep(10);
	fork();
	sleep(10);
	printf("PID#: %d\tPPID#: %d\n", getpid(), getppid());
	for (i=0; i<limit; i++) {
		printf("%d\n", i);
	}
	return 0;
}
