#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

typedef struct {
	pthread_t *thread;
} Thread;

int thread_new(Thread **, void *(*)(void *));
int thread_wait(Thread *);
int thread_delete(Thread *);

#endif // THREAD_H_
