/*
 *
*/
#include "extra.h"
#include "hash.h"

#include <stdbool.h>

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    return n;
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n) {
}
