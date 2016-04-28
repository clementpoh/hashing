#ifndef HASH_H
#define HASH_H

/* Used as the second hashing function on double hash */
unsigned int linear_probe(void *e, unsigned int size);

/* Very simple hash */
unsigned int worst_hash(void *e, unsigned int size);

/* Bad hash function */
unsigned int bad_hash(char *key, unsigned int size);

/* Basic numeric hash function */
unsigned int basic_hash(long n, unsigned int size);

/* Universal hash function as described in Dasgupta et. al 1.5.2 */
unsigned int universal_hash(unsigned char *key, unsigned int size);

#endif
