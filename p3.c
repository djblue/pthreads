#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_PASSENGERS 500

sem_t loading, loaded, unloading, unloaded;

int n, c;

void *passenger (void *tid) {
  int i = *((int*) tid);

  while (1) {

    sem_wait(&loading);
    printf("pass(i=%d).board()\n", i);
    sem_post(&loaded);

    sem_wait(&unloading);
    printf("pass(i=%d).unboard()\n", i);
    sem_post(&unloaded);

  }
}

void *roller_coaster () {
  while (1) {

    printf("car.load(c=%d)\n", c);
    for (int i = 0; i < c; i++) {
      sem_post(&loading);
    }

    // wait for c passengers to load
    for (int i = 0; i < c; i++) {
      sem_wait(&loaded);
    }

    printf("car.run()\n");

    sleep(1);

    printf("car.unload(c=%d)\n", c);
    for (int i = 0; i < c; i++) {
      sem_post(&unloading);
    }

    // wait for c passengers to unload
    for (int i = 0; i < c; i++) {
      sem_wait(&unloaded);
    }

  }
}

int main () {

  printf("Number of passengers(n, n <= 500): ");
  scanf("%d", &n);
  printf("Number of passengers per cart(c, c < n): ");
  scanf("%d", &c);

  sem_init(&loading, 0, 0);
  sem_init(&unloading, 0, 0);

  sem_init(&loaded, 0, 0);
  sem_init(&unloaded, 0, 0);

  pthread_t car;
  pthread_t tid[MAX_PASSENGERS];

  int my_ids[MAX_PASSENGERS];

  pthread_create(&car, NULL, roller_coaster, NULL);

  for (int i = 0; i < n; i++) {
    my_ids[i] = i;
    pthread_create(&tid[i], NULL, passenger, &my_ids[i]);
  }

  pthread_join(car, NULL);

  return 0;
}
