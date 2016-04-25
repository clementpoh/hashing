
#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdbool.h>

typedef struct hash_table_t *HashTable;
typedef void *Elem;
typedef void *Bucket;

/* Hash functions take the key, the table size and the probe */
typedef int (*Hash)(Elem d, int size, int probe);
typedef bool (*Eq)(Elem, Elem);
typedef void (*Print)(FILE *, Elem);

/* Functions for the buckets */
typedef void (*bucket_insert_fn)(Bucket*, Elem);
typedef Elem (*bucket_search_fn)(Eq, Bucket, Elem);
typedef void (*bucket_print_fn)(Print, FILE*, Bucket);

struct hash_table_t {
    /* Number of elements */
    int size;

    // hash function
    Hash hash1;
    // second hash function for double hashing
    Hash hash2;

    // functions for individual elements
    Eq eq;
    Print print;

    bucket_search_fn _search;
    bucket_insert_fn _insert;
    bucket_print_fn _print;

    // An array of buckets, either array of array_t* or list_t*
    Bucket *table;

};

// Create a new hash table, separate chaining with arrays
HashTable new_hash_array(int size, Hash hash, Eq eq, Print print);

// Create a new hash table, separate chaining with arrays and move-to-front
HashTable new_hash_array_MTF(int size, Hash hash, Eq eq, Print print);

// Create an empty hash table, separate chaining with linked lists
HashTable new_hash_list(int size, Hash hash, Eq eq, Print print);

// Create an empty hash table, separate chaining with linked and move-to-front
HashTable new_hash_list_MTF(int size, Hash hash, Eq eq, Print print);

// Create an empty hash table with open addressing using double hashing
HashTable new_hash_double(int size, Hash h1, Hash h2, Eq eq, Print print);

// Search table for e and return its pointer if found, else NULL
Elem hash_search(HashTable ht, Elem e);

// insert element into table
void hash_insert(HashTable ht, Elem e);

// print the whole table
void hash_print(HashTable ht, FILE *file);

#endif
