#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

int i;
sem_t a, b, c;

void *huey () {
  while (1) {
    printf("Huey(%d)\n", i);
    sleep(1);
    sem_post(&b);
    sem_wait(&a);
    i++;
  }
}

void *dewey () {
  while (1) {
    sem_wait(&b);
    printf("Dewey(%d)\n", i);
    sleep(1);
    sem_post(&c);
  }
}

void *louie () {
  while (1) {
    sem_wait(&c);
    printf("Louie(%d)\n", i);
    sleep(1);
    sem_post(&a);
  }
}

int main () {

  i = 0;
  pthread_t tid[3];

  sem_init(&a, 0, 0);
  sem_init(&b, 0, 0);
  sem_init(&c, 0, 0);

  pthread_create(&tid[0], NULL, huey, NULL);
  pthread_create(&tid[1], NULL, dewey, NULL);
  pthread_create(&tid[2], NULL, louie, NULL);

  pthread_join(tid[0], NULL);

  return 0;
}
