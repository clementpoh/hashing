#include "hash.h"

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

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

unsigned int universal_hash(char *key, unsigned int size) {
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

    for (int i = 0; i < len; i++)
        cs[i] = rand();

    return cs;
}
