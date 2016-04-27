#include "hash.h"

unsigned int bad_hash(Elem e, unsigned int size) {
    (void) e;
    (void) size;
    return 0;
}

unsigned int linear_probe(Elem e, unsigned int size) {
    (void) e;
    (void) size;
    return 1;
}

unsigned int basic_hash(long v, unsigned int size) {
    return v % size;
}

