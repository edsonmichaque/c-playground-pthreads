#include <pthread.h>
#include <stdlib.h>
#include <thread.h>

thread_error_t *
thread_error_new(int code, char *msg)
{
	/* Initialize an instance of thread_error_t */
	thread_error_t *err = (thread_error_t *)calloc(1,
	    sizeof(thread_error_t));
	err->code = code;
	err->msg = msg;

	return err;
}

/*  Free the object of type thread_error_t */
void
thread_error_free(thread_error_t *err)
{
	if (NULL == err) {
		free(err);
	}
}

/* Create a new thread by passing a function handler */
thread_error_t *
thread_new(thread_t **self, void *(*handler)(void *))
{

	thread_t *parent = (thread_t *)calloc(1, sizeof(thread_t));
	if (NULL == parent) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	if (NULL == self) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	pthread_t *thread = (pthread_t *)calloc(1, sizeof(pthread_t));
	if (NULL == thread) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	if (pthread_create(thread, NULL, handler, NULL)) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	parent->thread = thread;

	*self = parent;

	return NULL;
}

thread_error_t *
thread_wait(thread_t *self)
{
	/* Validate if thread is freed */
	if (NULL == self) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	if (NULL == self->thread) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	if (pthread_join(*(self->thread), NULL)) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	return NULL;
}

thread_error_t *
thread_free(thread_t *self)
{
	if (NULL == self) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	if (NULL == self->thread) {
		return thread_error_new(THREAD_ERR_FAILURE,
		    "unable to create parent");
	}

	if (NULL != self->thread) {
		free(self->thread);
	}

	if (NULL != self) {
		free(self);
	}

	return NULL;
}
