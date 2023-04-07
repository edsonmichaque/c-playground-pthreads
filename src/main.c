#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread.h>
#include <unistd.h>

void usage(void);
void *worker(void *);

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		usage();
	}

	int N_THREADS = atoi(argv[1]);

	Thread *threads[N_THREADS];
	for (int i = 0; i < N_THREADS; i++) {
		if (thread_new(&threads[i], worker)) {
			perror("thread_new");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < N_THREADS; i++) {
		if (thread_wait(threads[i])) {
			perror("thread_join");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < N_THREADS; i++) {
		if (thread_delete(threads[i])) {
			perror("thread_delete");
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}

void
usage(void)
{
	fprintf(stderr, "main <threads>");
	exit(EXIT_FAILURE);
}

void *
worker(void *args)
{

	for (int i = 0; i < 100; i++) {
		printf("thread=%lu sleep=%d\n",
		    (unsigned long int)pthread_self(), i);
		sleep(1);
	}

	return NULL;
}
