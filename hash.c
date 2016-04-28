#include "hash.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

static int *init_universal(int len);

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

unsigned int univ_hash(char *key, unsigned int size) {
    static int *cs = NULL;
    static int len = 0;

    if (!len) {
        len = log2(size) + 1;
        cs = init_universal(len);
    }

    unsigned int hash = 0;
    for (int i = 0; i < len && key[i]; i++)
        hash += cs[i] * key[i];

    return hash % size;
}

unsigned int linear_probe(Elem e, unsigned int size) {
    (void) e;
    (void) size;
    return 1;
}

static int *init_universal(int len) {
    int *cs = calloc(len, sizeof(*cs));

    for (int i = 0; i < len; i++) {
        cs[i] = rand();
    }

    return cs;
}

void collide_dumb(unsigned int size, unsigned int seed) {
    /* Reseed the random number generator */
    srand(seed);

    int len = log2(size) + 1; 
    int *cs = init_universal(len);

    /* Plus an extra for a null byte */
    int *invs = calloc(len + 1, sizeof(*invs));
    int *inv2 = calloc(len + 1, sizeof(*inv2));

    for (int i = 0; i < len; i++) {
        int j = 1;
        while (j * cs[i] % size) 
            j++;
       
        invs[i] = j;
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < len; j++) {
            inv2[j] = invs[j] * i;
        }
        printf("universal hash: %d: %d\n", i, univ_hash(inv2, size));
    }
}

void collide_clever(unsigned int size, unsigned int seed) {
}
