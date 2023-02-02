#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void* doGreeting(void* arg);

// global (shared and specific) data
int sharedData = 5;
char sampleArray[2] = {'a','b'};

int main() {
	pthread_t thread1, thread2;
	void *result1, *result2;
	int threadStatus1, threadStatus2;
	int joinStatus1, joinStatus2;

	threadStatus1 = pthread_create (&thread1, NULL, doGreeting, &sampleArray[0]);
	if (threadStatus1 != 0){
		fprintf (stderr, "Thread create error %d: %s\n", threadStatus1, strerror(threadStatus1));
		exit (1);
	}

	threadStatus2 = pthread_create(&thread2, NULL, doGreeting, &sampleArray[1]);
	if (threadStatus2 != 0) {
		fprintf (stderr, "thread create error %d: %s\n", threadStatus2, strerror(threadStatus2));
		exit (1);
	}

	printf ("Parent sees %d\n", sharedData);
	sharedData++;

	joinStatus1 = pthread_join(thread1, &result1);
	if (joinStatus1 != 0) {
		fprintf (stderr, "Join error %d: %s\n", joinStatus1, strerror(joinStatus1));
		exit (1);
	}

	joinStatus2 = pthread_join(thread2, &result2);
	if (joinStatus2 != 0) {
		fprintf (stderr, "Join error %d: %s\n", joinStatus2, strerror(joinStatus2));
		exit (1);
	}

	printf ("Parent sees %d\n", sharedData);
	return 0;
}

void* doGreeting(void* myArgument) {
	char *myPtr = (char *)myArgument;
	printf ("Child receiving %c initially sees %d\n", *myPtr, sharedData);
	sleep(1);
	sharedData++;
	printf ("Child receiving %c now sees %d\n", *myPtr, sharedData);
	return NULL;
}