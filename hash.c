#include "hash.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define MAXSTRLEN 256

static void init_universal(int cs[], int len, int size);

unsigned int worst_hash(Elem e, unsigned int size) {
    (void) e;
    (void) size;
    return 0;
}

/* Only works with numeric types */
unsigned int basic_hash(long n, unsigned int size) {
    return n % size;
}

unsigned int bad_hash(char *key, unsigned int size) {
    static int c = 0;

    if (!c) c = rand();

    return c * key[0] % size;
}

unsigned int universal_hash(unsigned char *key, unsigned int size) {
    static int cs[MAXSTRLEN];

    if (!cs[0]) {
        init_universal(cs, MAXSTRLEN, size);
    }

    unsigned int hash = 0;
    for (int i = 0; i < MAXSTRLEN && key[i]; i++)
        hash += cs[i] * key[i];

    return hash % size;
}

unsigned int linear_probe(Elem e, unsigned int size) {
    (void) e;
    (void) size;
    return 1;
}

static void init_universal(int cs[], int len, int size) {
    for (int i = 0; i < len; i++) {
        cs[i] = rand() % size;
    }
}
