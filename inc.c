// ***********************************************************************
// Example of use of pthreads library.
// 
// Save this program in "inc.cc", then compile on Linux using:
//    g++ -o inc inc.cc -lpthread
// To execute, run the associated executable (specified on the -o option).  
// The program will prompt for the number of threads to create.  Each 
// thread will then increment a counter UPPER times.  The counter is 
// global, i.e., shared, and so the access to it is protected by a binary 
// semaphore.
// ***********************************************************************

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

// Global constants

const int MAX = 500;    // Maximum number of threads allowed
const int UPPER = 1000; // Number of times the counter is incremented by
			// each thread

// Global variables

int counter = 0;        // variable to be incremented by each thread 
sem_t mutex;

// ***********************************************************************
// Function that each thread will execute.  If the semaphores work
// properly, then the function will effectively do, count += UPPER.
// ***********************************************************************

void *increment (void *arg) {
	// Parameter passed is the thread number.  Since the parameter could be 
	// anything, it is passed as void * and must be "converted".

	int id = *((int*) arg);

	//printf("Thread %d is starting.\n", id);

	// Simply iterate UPPER times, incrementing the counter each iteration.
	// Since the variable counter is a shared/global variable, protect
	// the modification of the variable by a semaphore.

	for (int j = 0; j < UPPER; j++) {
    sem_wait(&mutex);
		counter++;
    sem_post(&mutex);
	}

	//printf("Thread %d is ending.\n", id);
	return NULL;
}

// ***********************************************************************
// The main program:
//    1) Reads in, n, the number of threads to create.
//    2) Creates n threads, each one identical, and running the
//       increment() function.
//    3) Wait for each thread to complete execution.  Since each thread
//       simply increments the counter UPPER times, the value of the
//       counter when each thread terminates should be n*UPPER.
// ***********************************************************************

int main () {

	int i, no_threads;
  sem_init(&mutex, 0, 1);

  pthread_t tid[MAX];   // array of thread identifiers
  int my_ids[MAX];

	// Prompt for number of threads.  Default to four if an invalid number
	// is given.

	printf("Enter number of threads to create (< %d):\n", MAX);
	scanf("%d", &no_threads);

	if ((no_threads <= 0) || (no_threads >= MAX)) {
		printf("Invalid thread count -- defaulting to 4\n");
		no_threads = 4;
	}

	// Create no_threads identical threads each one running the increment()
	// function, saving the thread-id in the tid array, and using the default 
	// attributes.  Each thread calls the function increment(), with one
	// argument "i", used as the thread number.

	for (i = 0; i < no_threads; i++) {
    my_ids[i] = i;
		pthread_create(&tid[i], NULL, increment, &my_ids[i]);
  }

	// Wait for all the threads to exit.  This suspends the calling thread,
	// i.e., the main program, until all target threads complete.

	for (i = 0; i < no_threads; i++) {
		pthread_join(tid[i], NULL);
  }
  
	// Display final contents of counter.  We know what the value should
	// be if the mutual exclusion semaphores worked properly.

	printf("\nFinal value of counter is: %d (should be %d).\n", counter, no_threads*UPPER);
	printf("Each of %d threads adds %d to the counter.\n", no_threads, UPPER);
	return 0;
}
