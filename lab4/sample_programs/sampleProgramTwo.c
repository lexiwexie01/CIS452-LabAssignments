#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void* doGreeting(void* myArgument);

int threadCounter = 0;

int main() {
	pthread_t thread1, thread2; // thread ID's
	void *result1, *result2; // return values
	int threadStatus1, threadStatus2; // store the result of the thread creation
	int joinStatus1, joinStatus2; // store the result of the thread join

	threadStatus1 = pthread_create(&thread1, NULL, doGreeting, "hi");
	if(threadStatus1 != 0){
		fprintf (stderr, "Thread create error %d: %s\n", threadStatus1, strerror(threadStatus1));
		exit (1);
	}

	threadStatus2 = pthread_create(&thread2, NULL, doGreeting, "bye");
	if(threadStatus2 != 0) {
		fprintf(stderr, "Thread create error %d: %s\n", threadStatus2, strerror(threadStatus2));
		exit (1);
	}

	// join with the threads (wait for them to terminate); get their return vals
	joinStatus1 = pthread_join(thread1, &result1);
	if(joinStatus1 != 0) {
		fprintf(stderr, "Join error %d: %s\n", joinStatus1, strerror(joinStatus1));
		exit (1);
	}

	joinStatus2 = pthread_join(thread2, &result2);
	if(joinStatus2 != 0) {
		fprintf(stderr, "Join error %d: %s\n", joinStatus2, strerror(joinStatus2));
		exit (1);
	}

	printf("Thread one returned: [%s]\n", (char *)result1);
	printf("Thread two returned: [%s]\n", (char *)result2);
	return 0;
}

// function called by the threads, will print out a different message based on the argument passed to it
void* doGreeting(void* myArgument) {

	printf("String passed = %s\n", (char*)myArgument);

	threadCounter = threadCounter + 1;

	printf("ThreadCounter = %d\n", threadCounter);

	// Print out a message based on the argument passed to us
	for (int loop = 0; loop < 10; loop++) {
		sleep(1);
		if (strcmp((char*)myArgument, "hi")==0) {
			printf("Hello\n");
		} else{
			printf("Good Bye\n");
		}
	}

	if (strcmp((char*)myArgument, "hi") == 0) {
		myArgument = "Hello is done";
	} else{
		myArgument = "Good Bye is done";
	}
	return myArgument;
}