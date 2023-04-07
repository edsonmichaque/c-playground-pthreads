#include <pthread.h>
#include <stdlib.h>
#include <thread.h>

int
thread_new(Thread **self, void *(*handler)(void *))
{
	Thread *parent = (Thread *)calloc(1, sizeof(Thread));
	if (NULL == parent) {
		return 1;
	}

	if (NULL == self) {
		return 1;
	}

	pthread_t *thread = (pthread_t *)calloc(1, sizeof(pthread_t));
	if (NULL == thread) {
		return 1;
	}

	if (pthread_create(thread, NULL, handler, NULL)) {
		return 1;
	}

	parent->thread = thread;

	*self = parent;

	return 0;
}

int
thread_wait(Thread *self)
{
	if (NULL == self) {
		return 1;
	}

	if (NULL == self->thread) {
		return 1;
	}

	if (pthread_join(*(self->thread), NULL)) {
		return 1;
	}

	return 0;
}

int
thread_delete(Thread *self)
{
	if (NULL == self) {
		return 1;
	}

	if (NULL == self->thread) {
		return 1;
	}

	if (NULL != self->thread) {
		free(self->thread);
	}

	if (NULL != self) {
		free(self);
	}

	return 0;
}
