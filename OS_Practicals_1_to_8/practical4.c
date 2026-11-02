#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;
    int round;

    for (round = 1; round <= 2; round++) {
        printf("Philosopher %d is thinking.\n", id + 1);

        sem_wait(&room);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        printf("Philosopher %d is eating (round %d).\n", id + 1, round);
        sleep(1);

        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&room);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[N];
    int ids[N];
    int i;

    sem_init(&room, 0, N - 1);

    for (i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    for (i = 0; i < N; i++)
        sem_destroy(&forks[i]);

    sem_destroy(&room);
    printf("All philosophers finished eating.\n");
    return 0;
}
