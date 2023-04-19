#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define SIZE 30

int main (int argc, char *argv[]) {
	struct flock fileLock;
	int fd;
	char myBuffer[SIZE] = "// where did this come from?";
	
	if (argc < 2) {
		printf("usage: filename\n");
		exit(1);
	}
	if ((fd = open(argv[1], O_RDWR)) < 0) {
		perror("there is");
		exit(1);
	}
	
	fileLock.l_type = F_WRLCK;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = 0;
	fileLock.l_len = 0;
	
	// sleep while the file is not available
	while (fcntl(fd, F_SETLK, &fileLock) == -1) {
		if (errno == EAGAIN || errno == EACCES) {
			sleep(1);
		} else {
			perror("Unable to set file lock");
			exit(1);
		}
	}
	
	// read and print the first line of the file
	if (read(fd, myBuffer, SIZE-1) == -1) {
		perror("Unable to read file");
		exit(1);
	}
	myBuffer[SIZE-1] = '\0';
	printf("First line of file: %s\n", myBuffer);
	
	// release the lock and close the file
	fileLock.l_type = F_UNLCK;
	if (fcntl(fd, F_SETLK, &fileLock) == -1) {
		perror("Unable to unlock  file lock");
		exit(1);
	}
	
	close(fd);
	
	return(0);
}
