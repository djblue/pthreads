#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int n;
sem_t mutex, produced;

void *consumer () {
  while (1) {
    sleep(rand()%3);
    printf("wait(mutex);\n");
    sem_wait(&mutex);
    printf("take();\n");
    n--;
    printf("n = %d;\n", n);
    sem_post(&mutex);
    printf("consume();\n");
    if (n == 0) {
      sem_wait(&produced);
    }
  }
}

void *producer () {
  while (1) {
    sleep(rand()%3);
    printf("produce();\n");
    printf("wait(mutex);\n");
    sem_wait(&mutex);
    printf("append();\n");
    n++;
    printf("n = %d;\n", n);
    if (n == 1) {
      sem_post(&produced);
    }
    sem_post(&mutex);
  }
}

int main () {

  n = 0;
  pthread_t tid[2];

  sem_init(&mutex, 0, 1);
  sem_init(&produced, 0, 0);

  pthread_create(&tid[0], NULL, producer, NULL);
  pthread_create(&tid[1], NULL, consumer, NULL);

  pthread_join(tid[0], NULL);

  return 0;
}
