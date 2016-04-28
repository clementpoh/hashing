#ifndef PRIMES_H
#define PRIMES_H

/* Determine appropriate size of hash table */
unsigned int determine_size(unsigned int n);

void collide_dumb(unsigned int size, unsigned int seed);

void collide_clever(unsigned int size, unsigned int seed);

#endif
