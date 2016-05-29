/*
 *
*/
#include "hash.h"

#include <stdlib.h>

#define MAXSTRLEN 256

/* Used as the second hashing function on double hash */
unsigned int linear_probe(void *e, unsigned int size) {
    return 0;
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
    return 0;
}

/* Universal hash function as described in Dasgupta et al 1.5.2 */
unsigned int universal_hash(unsigned char *key, unsigned int size) {
    return 0;
}
