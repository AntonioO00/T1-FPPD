#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILOSOFOS 5
#define ITERACOES 100

sem_t garfos[FILOSOFOS];
sem_t semaforo;
int contagemComidas[FILOSOFOS] = {0};

void* filosofo(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITERACOES; i++) {
        sem_wait(&semaforo); // Aguarda permissão para sentar
        printf("Filósofo %d senta\n", id);
        if (id % 2 == 0) {
            sem_wait(&garfos[id]);
            printf("Filósofo %d pegou o primeiro garfo\n", id);
            sem_wait(&garfos[(id + 1) % FILOSOFOS]);
            printf("Filósofo %d pegou o segundo garfo\n", id);
        } else {
            sem_wait(&garfos[(id + 1) % FILOSOFOS]);
            printf("Filósofo %d pegou o segundo garfo\n", id);
            sem_wait(&garfos[id]);
            printf("Filósofo %d pegou o primeiro garfo\n", id);
        }

        contagemComidas[id]++;
        sem_post(&garfos[id]);
        sem_post(&garfos[(id + 1) % FILOSOFOS]);
        printf("Filósofo %d liberou os garfos\n", id);
        sem_post(&semaforo); // Libera a permissão para outro filósofo
    }
    return NULL;
}

int main() {
    pthread_t filosofos[FILOSOFOS];
    int ids[FILOSOFOS];

    sem_init(&semaforo, 0, 2); // Limitar a 2 filósofos comendo
    for (int i = 0; i < FILOSOFOS; i++) {
        sem_init(&garfos[i], 0, 1);
        ids[i] = i;
    }

    for (int i = 0; i < FILOSOFOS; i++) {
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < FILOSOFOS; i++) {
        pthread_join(filosofos[i], NULL);
    }

    for (int i = 0; i < FILOSOFOS; i++) {
        printf("Filósofo %d comeu %d vezes.\n", i, contagemComidas[i]);
    }

    for (int i = 0; i < FILOSOFOS; i++) {
        sem_destroy(&garfos[i]);
    }
    sem_destroy(&semaforo);

    return 0;
}
