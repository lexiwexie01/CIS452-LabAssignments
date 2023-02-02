#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* doGreeting(void* arg);

int main() {
	printf("Running the program\n");

	pthread_t thread1; // thread ID holder

	int threadStatus; // captures any error code

	// create and start a thread executing the "doGreeting()" function
	threadStatus = pthread_create (&thread1, NULL, doGreeting, NULL);
	if (threadStatus != 0) {
		fprintf (stderr, "Thread create error %d: %s\n", threadStatus, strerror(threadStatus));
		exit (1);
	}
	sleep(2);
	return 0;
}

void* doGreeting (void* arg) {
	sleep(1);
	printf ("Thread version of Hello, world.\n");
	return arg;
}