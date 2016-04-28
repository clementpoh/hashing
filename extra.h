#ifndef PRIMES_H
#define PRIMES_H

/* Determine appropriate size of hash table */
unsigned int determine_size(unsigned int n);

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n);

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n);

#endif
