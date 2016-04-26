
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdbool.h>

#include "hash.h"

/* Some type definitions for convenience */
typedef struct hash_table_t *HT;
typedef void *Bucket;

typedef bool (*Eq)(Elem e1, Elem e2);
typedef void (*Print)(FILE *file, Elem e);

/* Functions for the buckets */
typedef void (*bucket_insert_fn)(Bucket *b, Elem e);
typedef Elem (*bucket_search_fn)(Eq eq_fn, Bucket b, Elem e);
typedef Elem (*bucket_search_MTF_fn)(Eq eq_fn, Bucket *b, Elem e);
typedef void (*bucket_print_fn)(Print print, FILE *f, Bucket b);

struct hash_table_t {
    /* Number of elements */
    unsigned int size;

    /* Mimicking parametric polymorphism in C */

    /* hash function */
    Hash hash1;
    /* second hash function for double hashing */
    Hash hash2;

    /* Functions to operate on individual elements */
    Eq eq;
    Print print;

    /* Functions to operate on buckets for separate chaining */
    bucket_search_fn _search;
    bucket_search_MTF_fn _search_MTF;
    bucket_insert_fn _insert;
    bucket_print_fn _print;

    void (*table_insert)(HT ht, Elem e);
    void (*table_search)(HT ht, Elem e);


    /* An array of buckets, either array of array_t* or list_t* */
    Bucket *table;
};

/* Create a new hash table, separate chaining with arrays */
HT new_hash_array(unsigned int size, Hash hash, Eq eq, Print print);

/* Create a new hash table, separate chaining with arrays and move-to-front */
HT new_hash_array_MTF(unsigned int size, Hash hash, Eq eq, Print print);

/* Create a hash table, separate chaining with linked lists */
HT new_hash_list(unsigned int size, Hash hash, Eq eq, Print print);

/* Create a hash table, separate chaining with linked and move-to-front */
HT new_hash_list_MTF(unsigned int size, Hash hash, Eq eq, Print print);

/* Create a  hash table with open addressing using linear probing */
HT new_hash_linear(unsigned int size, Hash hash, Eq eq, Print print);

/* Create a  hash table with open addressing using double hashing */
HT new_hash_double(unsigned int size, Hash h1, Hash h2, Eq eq, Print print);

/* Search table for e and return its pointer if found, else NULL */
Elem hash_search(HT ht, Elem e);

/* insert element into table */
void hash_insert(HT ht, Elem e);

/* print the whole table */
void hash_print(HT ht, FILE *file);

#endif
