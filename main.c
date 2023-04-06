#include "thread.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage(void);
void *worker(void *);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage();
  }

  int n_theard = atoi(argv[1]);

  pthread_t threads[n_theard];
  thread_info_t threads_info[n_theard];

  for (int i = 0; i < n_theard; i++) {
    threads_info[i] = (thread_info_t){
        .id = i,
        .sleep = i,
    };
  }

  for (int i = 0; i < n_theard; i++) {
    if (pthread_create(&threads[i], NULL, &worker, &threads_info[i])) {
      perror("pthread_create");
    }
  }

  for (int i = 0; i < n_theard; i++) {
    if (pthread_join(threads[i], NULL)) {
      perror("pthread_join");
    }
  }

  return EXIT_SUCCESS;
}

void usage(void) {
  fprintf(stderr, "main <threads>");
  exit(EXIT_FAILURE);
}

void *worker(void *args) {
  thread_info_t *thread_info = (thread_info_t *)args;

  for (int i = 0; i < 100; i++) {
    printf("thread=%lu sleep=%d\n", (unsigned long int)pthread_self(), i);
    sleep(thread_info->sleep);
  }

  return NULL;
}
