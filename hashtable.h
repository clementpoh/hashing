
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdbool.h>

#include "hash.h"

/* Some type definitions for convenience */
typedef struct hash_table_t *HT;
typedef void *Bucket;

/* Functions to operate on individual table elements */
typedef bool (*Eq)(Elem e1, Elem e2);
typedef Elem (*Parse)(char *str);
typedef void (*Print)(FILE *file, Elem e);

/* Keep track of them in a struct */
typedef struct {
    Eq eq;
    Parse parse;
    Print print;
} Type;

/* Functions for the buckets */
typedef Elem (*bucket_insert_fn)(Bucket *b, Elem e);
typedef Elem (*bucket_search_fn)(Eq eq_fn, Bucket b, Elem e);
typedef Elem (*bucket_search_MTF_fn)(Eq eq_fn, Bucket *b, Elem e);
typedef void (*bucket_print_fn)(Print print, FILE *f, Bucket b);

typedef enum {
    LIST,
    ARRAY,
    LINEAR,
    DOUBLE,
} Chain;

struct hash_table_t {
    /* Number of elements */
    unsigned int size;

    /* Mimicking parametric polymorphism in C */
    /* Hash function */
    Hash hash1;
    /* Second hash function for double hashing */
    Hash hash2;

    /* Functions to operate on individual elements */
    Eq eq;
    Parse parse;
    Print print;

    /* Functions to operate on buckets for separate chaining */
    bucket_search_fn _search;
    bucket_search_MTF_fn _search_MTF;
    bucket_insert_fn _insert;
    bucket_print_fn _print;

    /* An array of buckets, either array of array_t* or list_t* */
    Bucket *table;

    /* The following fields aren't strictly necessary */
    Chain method;
    bool MTF;
};

/* Create a new hash table, separate chaining with arrays */
extern HT new_hash_array(unsigned int size, Hash hash, Type t);

/* Create a new hash table, separate chaining with arrays and move-to-front */
extern HT new_hash_array_MTF(unsigned int size, Hash hash, Type t);

/* Create a hash table, separate chaining with linked lists */
extern HT new_hash_list(unsigned int size, Hash hash, Type t);

/* Create a hash table, separate chaining with linked and move-to-front */
extern HT new_hash_list_MTF(unsigned int size, Hash hash, Type t);

/* Create a  hash table with open addressing using linear probing */
extern HT new_hash_linear(unsigned int size, Hash hash, Type t);

/* Create a  hash table with open addressing using double hashing */
extern HT new_hash_double(unsigned int size, Hash h1, Hash h2, Type t);

/* Load data into ht from file */
extern void hash_load(HT ht, FILE *file);

/* Search ht for each elem in file */
extern void hash_search_file(HT ht, FILE *file);

/* print the whole table */
extern void hash_print(HT ht, FILE *file);

/* Search table for e and return its pointer if found, else NULL */
extern Elem hash_search(HT ht, Elem e);

/* insert element into table */
extern void hash_insert(HT ht, Elem e);

#endif
