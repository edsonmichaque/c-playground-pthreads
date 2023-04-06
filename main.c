#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct info {
  char *name;
  int sleep;
} thread_info_t;

void *worker(void *args) {
  thread_info_t *thread_info = (thread_info_t *)args;

  for (int i = 0; i < 100; i++) {
    printf("thread=%s i=%d\n", thread_info->name, i);
    sleep(thread_info->sleep);
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2;

  thread_info_t thread_1_info = {
      .name = "t1",
      .sleep = 1,
  };

  thread_info_t thread_2_info = {
      .name = "t2",
      .sleep = 4,
  };

  if (pthread_create(&t1, NULL, &worker, &thread_1_info)) {
    perror("pthread_create");
  }

  if (pthread_create(&t2, NULL, &worker, &thread_2_info)) {
    perror("pthread_create");
  }

  if (pthread_join(t1, NULL)) {
    perror("pthread_join");
  }

  if (pthread_join(t2, NULL)) {
    perror("pthread_join");
  }

  return EXIT_SUCCESS;
}
