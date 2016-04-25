#include <stdlib.h>
#include <assert.h>

#include "hashtable.h"
#include "list.h"
#include "array.h"

static HashTable new_hash(int size, Hash h1, Hash h2, Eq eq, Print print);

static HashTable new_hash(int size, Hash h1, Hash h2, Eq eq, Print print) {
    HashTable ht = calloc(1, sizeof(*ht));
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

// Create an empty hash table, using arrays for separate chaining
HashTable new_hash_array(int size, Hash hash, Eq eq, Print print) {
    HashTable ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) array_insert;
    ht->_search = (bucket_search_fn) array_find;
    ht->_print = (bucket_print_fn) array_fprint;

    return ht;
}

// Create an empty hash table, using arrays for separate chaining
HashTable new_hash_array_MTF(int size, Hash hash, Eq eq, Print print) {
    HashTable ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) array_insert_MTF;
    ht->_search = (bucket_search_fn) array_find_MTF;
    ht->_print = (bucket_print_fn) array_fprint;

    return ht;
}

HashTable new_hash_list(int size, Hash hash, Eq eq, Print print) {
    HashTable ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) list_insert;
    ht->_search = (bucket_search_fn) list_find;
    ht->_print = (bucket_print_fn) list_fprint;

    return ht;
}

HashTable new_hash_list_MTF(int size, Hash hash, Eq eq, Print print) {
    HashTable ht = new_hash(size, hash, NULL, eq, print);

    ht->_insert = (bucket_insert_fn) list_prepend;
    ht->_search = (bucket_search_fn) list_find;
    ht->_print = (bucket_print_fn) list_fprint;

    return ht;
}

void hash_insert(HashTable ht, Elem e) {
    int b = ht->hash1(e, ht->size, 0);
    ht->_insert(&ht->table[b], e);
}

Elem hash_search(HashTable ht, Elem e) {
    int b = ht->hash1(e, ht->size, 0);
    return ht->_search(ht->eq, ht->table[b], e);
}

void hash_print(HashTable ht, FILE *file) {
    fprintf(file, "size: %d\n", ht->size);

    for (int i = 0; i < ht->size; i++) {
        fprintf(file, "%d: ", i);
        ht->_print(ht->print, file, ht->table[i]);
        fprintf(file, "\n");
    }
}
