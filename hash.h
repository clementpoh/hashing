#ifndef HASH_H
#define HASH_H

/* Elements that can be inserted into hash tables are arbitrary */
typedef void *Elem;

/* Hash functions take the key, the table size */
typedef unsigned int (*Hash)(Elem e, unsigned int size);

unsigned int worst_hash(Elem e, unsigned int size);

unsigned int bad_hash(char *key, unsigned int size);

unsigned int basic_hash(long n, unsigned int size);

unsigned int universal_hash(char *key, unsigned int size);

unsigned int linear_probe(Elem e, unsigned int size);
#endif
