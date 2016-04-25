/*
** COMP200007 Design of Algorithms
** Data structure to store an array of (key, void *) pairs, but
** stores them in separate arrays, first vals then ptrs.
**
** Author: Andrew Turpin
** Wed  8 May 2013 19:54:26 EST
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"

// create empty array
array_t *array_create(void) {
    array_t *A = malloc(sizeof(array_t));
    assert(A != NULL);

    A->size = 0;
    A->vals = NULL;

    return A;
}

void move_to_front(array_t *A, int pos) {
    void *head = A->vals[pos];

    for(int j = pos; j > 0; j--) {
        void *tmp = A->vals[j];
        A->vals[j] = A->vals[j - 1];
        A->vals[j - 1] = tmp;
    }

    A->vals[0] = head;
}

// add v to A
void array_insert(array_t **A, void *v) {
    if (!*A)
        (*A) = array_create();

    (*A)->size += 1;
    (*A)->vals = realloc((*A)->vals, sizeof((*A)->vals) * (*A)->size);
    assert((*A)->vals != NULL);

    (*A)->vals[(*A)->size - 1] = v;

}

void array_insert_MTF(array_t **A, void *v) {
    array_insert(A, v);
    move_to_front((*A), (*A)->size - 1);
}

void *array_find(bool (*eq)(void *, void *), array_t *A, void *v) {
    assert(A != NULL);
    int i = 0;

    for (i = 0; i < A->size; i++) {
        if (eq(v, A->vals[i]))
            return A->vals[i];
    }

    return NULL;
}

void *array_find_MTF(bool (*eq)(void *, void *), array_t *A, void *v) {
    assert(A != NULL);
    int i = 0;

    for (i = 0; i < A->size; i++) {
        if (eq(v, A->vals[i]))
            break;
    }

    // Could not find v in A
    if (i == A->size) {
        return NULL;
    } else if (i > 0) {
        move_to_front(A, i);
    }

    return A->vals[0];
}

void array_delete(bool (*eq)(void *, void *), array_t *A, void *v) {
    assert(A != NULL);
    int i = 0;

    for (i = 0 ; i < A->size; i++) {
        if (eq(v, A->vals[i]))
            break;
    }

    for (int j = i + 1; j < A->size; j++) {
        A->vals[j - 1] = A->vals[j];
    }
}

void array_fprint(void (*print)(FILE *f, void *data), FILE *f, array_t *A) {
    if (A) {
        for (int i = 0; i < A->size; i++) {
            print(f, A->vals[i]);
        }
    }
}
