#include "hash.h"

#include <stdlib.h>

unsigned int worst_hash(Elem e, unsigned int size) {
    (void) e;
    (void) size;
    return 0;
}

unsigned int bad_hash(Elem e, unsigned int size) {
    char *key = e;
    return rand() * key[0] % size;
}

unsigned int basic_hash(Elem e, unsigned int size) {
    return ((long) e) % size;
}

unsigned int universal_hash(Elem e, unsigned int size) {
    return 0;
}

unsigned int linear_probe(Elem e, unsigned int size) {
    (void) e;
    (void) size;
    return 1;
}

