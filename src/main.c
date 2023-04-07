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

	void *leak = calloc(1 << 30, 16);

	int N_THREADS = atoi(argv[1]);

	thread_t *threads[N_THREADS];
	for (int i = 0; i < N_THREADS; i++) {
		thread_error_t *err = thread_new(&threads[i], worker);

		if (err) {
			perror("thread_new_error");
			thread_error_delete(err);
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < N_THREADS; i++) {
		thread_error_t *err = thread_wait(threads[i]);

		if (err) {
			perror("thread_join");
			thread_error_delete(err);
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < N_THREADS; i++) {
		thread_error_t *err = thread_delete(threads[i]);

		if (err) {
			perror("thread_delete");
			thread_error_delete(err);
			exit(EXIT_FAILURE);
		}
	}

	sleep(1200);

	free(leak);

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

	for (int i = 0; i < 5; i++) {
		printf("thread=%lu sleep=%d\n",
		    (unsigned long int)pthread_self(), i);
		sleep(1);
	}

	return NULL;
}
