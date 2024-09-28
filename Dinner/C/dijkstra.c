#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILOSOFOS 5
#define ITERACOES 100

pthread_mutex_t garfos[FILOSOFOS];
int contagemComidas[FILOSOFOS] = {0};

void* filosofo(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITERACOES; i++) {
        printf("Filósofo %d senta\n", id);
        if (id % 2 == 0) {
            pthread_mutex_lock(&garfos[id]);
            printf("Filósofo %d pegou o primeiro garfo\n", id);
            pthread_mutex_lock(&garfos[(id + 1) % FILOSOFOS]);
            printf("Filósofo %d pegou o segundo garfo\n", id);
        } else {
            pthread_mutex_lock(&garfos[(id + 1) % FILOSOFOS]);
            printf("Filósofo %d pegou o segundo garfo\n", id);
            pthread_mutex_lock(&garfos[id]);
            printf("Filósofo %d pegou o primeiro garfo\n", id);
        }

        contagemComidas[id]++;
        pthread_mutex_unlock(&garfos[id]);
        pthread_mutex_unlock(&garfos[(id + 1) % FILOSOFOS]);
        printf("Filósofo %d liberou os garfos\n", id);
    }
    return NULL;
}

int main() {
    pthread_t filosofos[FILOSOFOS];
    int ids[FILOSOFOS];
    
    for (int i = 0; i < FILOSOFOS; i++) {
        pthread_mutex_init(&garfos[i], NULL);
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
        pthread_mutex_destroy(&garfos[i]);
    }

    return 0;
}
