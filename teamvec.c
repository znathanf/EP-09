#include "teamvec.h"
#include <stdio.h>
#include <stdlib.h>

#define TV_INITIAL_CAPACITY 4

struct teamvec {
    int size;       // número de times atualmente guardados
    int capacity;   // quantos times cabem no vetor interno
    Team **data;    // vetor alocado de ponteiros para Team
};

TeamVec *tv_create(void) {
    TeamVec *tv = malloc(sizeof(TeamVec));
    if (tv == NULL)
        return NULL;

    tv->data = malloc(TV_INITIAL_CAPACITY * sizeof(Team *));
    if (tv->data == NULL) {
        free(tv);
        return NULL;
    }

    tv->size = 0;
    tv->capacity = TV_INITIAL_CAPACITY;
    return tv;
}

void tv_insert(TeamVec *tv, Team *t) {
    if (tv == NULL || t == NULL)
        return;

    // vetor cheio: dobra a capacidade antes de gravar o novo ponteiro
    if (tv->size == tv->capacity) {
        int new_capacity = tv->capacity * 2;
        Team **new_data = realloc(tv->data, new_capacity * sizeof(Team *));
        if (new_data == NULL) {
            fprintf(stderr, "tv_insert: sem memoria para expandir o vetor\n");
            exit(EXIT_FAILURE);
        }
        tv->data = new_data;
        tv->capacity = new_capacity;
    }

    tv->data[tv->size] = t;
    tv->size++;
}

int tv_size(TeamVec *tv) {
    return tv->size;
}

Team *tv_get(TeamVec *tv, int i) {
    return tv->data[i];
}

void tv_free(TeamVec *tv) {
    if (tv == NULL)
        return;

    for (int i = 0; i < tv->size; i++)
        team_free(tv->data[i]);
    free(tv->data);
    free(tv);
}
