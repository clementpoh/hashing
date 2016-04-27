#include <stdlib.h>
#include <assert.h>

#include "hashtable.h"
#include "list.h"
#include "array.h"

/* Create a new arbitrary hash table */
static HT new_hash(unsigned int size, Hash h1, Hash h2, Eq eq, Print print);

/* Printing function used for open address hash tables */
static void open_address_print(Print print, FILE *file, Bucket b);

/* Find e in ht, ht uses double hashing */
static Bucket double_find(HT ht, unsigned int hash, Elem e);

/* Find the next free slot in ht, ht uses double hashing */
static Bucket *double_next_empty(HT ht, unsigned int hash, Elem e);

/* Create a new arbitrary hash table */
static HT new_hash(unsigned int size, Hash h1, Hash h2, Eq eq, Print print) {
    HT ht = calloc(1, sizeof(*ht));
    assert(ht);

    ht->table = calloc(size, sizeof(*ht->table));
    assert(ht->table);

    ht->size = size;
    ht->hash1 = h1;
    ht->hash2 = h2;
    ht->eq = eq;
    ht->print = print;

    return ht;
}

/* Create a new hash table, separate chaining with arrays */
HT new_hash_array(unsigned int size, Hash hash, Eq eq, Print print) {
    HT ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) array_insert;
    ht->_search = (bucket_search_fn) array_find;
    ht->_print = (bucket_print_fn) array_fprint;

    return ht;
}

/* Create an empty hash table, using arrays for separate chaining */
HT new_hash_array_MTF(unsigned int size, Hash hash, Eq eq, Print print) {
    HT ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) array_insert_MTF;
    ht->_search = (bucket_search_fn) array_find_MTF;
    ht->_print = (bucket_print_fn) array_fprint;

    return ht;
}

/* Create a hash table, separate chaining with linked lists */
HT new_hash_list(unsigned int size, Hash hash, Eq eq, Print print) {
    HT ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) list_insert;
    ht->_search = (bucket_search_fn) list_find;
    ht->_print = (bucket_print_fn) list_fprint;

    return ht;
}

HT new_hash_list_MTF(unsigned int size, Hash hash, Eq eq, Print print) {
    HT ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) list_prepend;
    ht->_search_MTF = (bucket_search_MTF_fn) list_find_MTF;
    ht->_print = (bucket_print_fn) list_fprint;

    return ht;
}

/* Create an empty hash table with open addressing using double hashing */
HT new_hash_double(unsigned int size, Hash h1, Hash h2, Eq eq, Print print) {
    HT ht = new_hash(size, h1, h2, eq, print);

    ht->_print = (bucket_print_fn) open_address_print;

    return ht;
}

HT new_hash_linear(unsigned int size, Hash hash, Eq eq, Print print) {
    return new_hash_double(size, hash, linear_probe, eq, print);
}

static void open_address_print(Print print, FILE *file, Bucket b) {
    print(file, b);
}

void hash_insert(HT ht, Elem e) {
    unsigned int hash = ht->hash1(e, ht->size);

    if (!ht->hash2) {
        ht->_insert(&ht->table[hash], e);
    } else {
        Bucket *bucket = double_next_empty(ht, hash, e);
        if (bucket)
            *bucket = e;
        else
            fprintf(stderr, "Aborting insertion: table full\n");
    }
}

Elem hash_search(HT ht, Elem e) {
    assert(ht);
    assert(ht->hash1);
    assert(ht->eq);

    unsigned int hash = ht->hash1(e, ht->size);

    if (!ht->hash2) {
        return ht->_search_MTF
            ? ht->_search_MTF(ht->eq, &ht->table[hash], e)
            : ht->_search(ht->eq, ht->table[hash], e);
    } else {
        return double_find(ht, hash, e);
    }
}

void hash_print(HT ht, FILE *file) {
    assert(ht);
    assert(ht->_print);
    assert(ht->print);

    fprintf(file, "size: %d\n", ht->size);

    for (unsigned int i = 0; i < ht->size; i++) {
        fprintf(file, "%d: ", i);
        ht->_print(ht->print, file, ht->table[i]);
        fprintf(file, "\n");
    }
}

static Bucket *double_next_empty(HT ht, unsigned int hash, Elem e) {
    unsigned int h = hash, i = 0;

    while (ht->table[h] && i <= ht->size) {
        h = (hash + i * ht->hash2(e, ht->size)) % ht->size;
        i++;
    }

    return i <= ht->size ? &ht->table[h] : NULL;
}

static Bucket double_find(HT ht, unsigned int hash, Elem e) {
    unsigned int h = hash, i = 0;

    while (!ht->eq(ht->table[h], e) && i <= ht->size) {
        h = (hash + i * ht->hash2(e, ht->size)) % ht->size;
        i++;
    }

    return i <= ht->size ? ht->table[h] : NULL;
}
