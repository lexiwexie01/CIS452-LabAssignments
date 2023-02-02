#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	int fd = open("test.txt", O_RDWR);
	if (fd < 0) {
		perror("file read error");
		return 1;
	}
	printf("fd:%d\n", fd);

	// This should redirect anything from stdin to test.txt
	// I'm not exactly sure how this works.
	dup2(fd, 0);

	// This will redirect anything from stdout to test.txt
	// That means that if we print anything, it'll go to 
	// test.txt
	dup2(fd, 1);
	printf("I'm in test.txt");

	return 0;
}