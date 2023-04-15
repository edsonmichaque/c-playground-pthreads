#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

#define THREAD_SUCCESS 0
#define THREAD_ERR_FAILURE 1

typedef struct {
	pthread_t *thread;
} thread_t;

typedef struct {
	int code;
	char *msg;
} thread_error_t;

thread_error_t *thread_new(thread_t **, void *(*)(void *));
thread_error_t *thread_wait(thread_t *);
thread_error_t *thread_free(thread_t *);
thread_error_t *thread_error_new(int code, char *msg);
void thread_error_free(thread_error_t *err);

#endif // THREAD_H_
