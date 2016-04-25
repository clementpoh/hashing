/*
** COMP200007 Design of Algorithms
** Data structure to store an array of (key, void *) pairs, but
** stores them in separate arrays, first vals then ptrs.
**
** Author: Andrew Turpin
** Wed  8 May 2013 19:21:49 EST
*/
#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct array {
    int size;
    void **vals;
} array_t;

void array_insert(array_t **A, void *k);

void array_insert_MTF(array_t **A, void *k);

void *array_find(bool (*eq)(void *, void *), array_t *A, void *v);

void *array_find_MTF(bool (*eq)(void *, void *), array_t *A, void *v);

void array_delete(bool (*eq)(void *, void *), array_t *A, void *k);

void array_fprint(void (*)(FILE *f, void *data), FILE *f, array_t *A);

#endif
