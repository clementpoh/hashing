/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module provides the functionality related to hash functions.
 *
*/
#include "hash.h"

#include <stdlib.h>

#define MAXSTRLEN 256

/* Initialise universal hash coefficients into cs */
static void init_universal(int cs[], int len, int size);

/* Used as the second hashing function on double hash */
unsigned int linear_probe(void *e, unsigned int size) {
    (void) e;
    (void) size;
    return 1;
}

/* Very simple hash */
unsigned int worst_hash(void *e, unsigned int size) {
    (void) e;
    (void) size;
    return 0;
}

/* Basic numeric hash function */
unsigned int num_hash(long n, unsigned int size) {
    return n % size;
}

/* Bad hash function */
unsigned int bad_hash(char *key, unsigned int size) {
    static int c = 0;

    if (!c) c = rand();

    return c * key[0] % size;
}

/* Universal hash function as described in Dasgupta et al 1.5.2 */
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

/* Initialise universal hash coefficients into cs */
static void init_universal(int cs[], int len, int size) {
    for (int i = 0; i < len; i++) {
        cs[i] = rand() % size;
    }
}
