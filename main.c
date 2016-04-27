#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>

#include "primes.h"
#include "hash.h"
#include "types.h"
#include "hashtable.h"

#define DEFAULT_SIZE 11

/* Struct to store the configuration options from the command line */
typedef struct {
    char *bin;
    char *insert;
    char *search;
    bool MTF;
    bool string;
    unsigned int size;
    Collision method;
} Options;

/* Print usage message and exit */
static void usage_exit(char *bin);

/* Load the the command line options into opts */
static Options load_options(int argc, char *argv[]);

static HT create_table(Options opts);

static void read_data(HT ht, char *filename);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s (method) [options] insert.in search.in\n", bin);
    fprintf(stderr, "Collision resolution method:\n");
    fprintf(stderr, "  -a       Separate chaining with an array\n");
    fprintf(stderr, "  -c       Separate chaining with a linked list\n");
    fprintf(stderr, "  -d       Open addressing with double hashing\n");
    fprintf(stderr, "  -l       Open addressing with linear probing\n");
    fprintf(stderr, "insert.in  File containing values to be inserted\n");
    fprintf(stderr, "search.in  File containing values to be searched\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -s       Input values are unsigned chars\n");
    fprintf(stderr, "  -m       Move-to-front for separate chaining\n");
    fprintf(stderr, "  -n size  Expected input size\n");

    exit(EXIT_FAILURE);
}

/* Load the the command line options into opts */
static Options load_options(int argc, char *argv[]) {
    extern char *optarg;
    extern int optind;
    int c;
    Options opts = {
        .bin    = argv[0],
        .insert = NULL,
        .search = NULL,
        .method = LIST,
        .MTF    = false,
        .string = false,
    };

    while ((c = getopt(argc, argv, "acdlmn:")) != -1) {
        switch (c) {
            case 'a': opts.method = ARRAY;      break;
            case 'c': opts.method = LIST;       break;
            case 'd': opts.method = DOUBLE;     break;
            case 'l': opts.method = LINEAR;     break;
            case 's': opts.string = true;       break;
            case 'm': opts.MTF  = true;         break;
            case 'n': opts.size = atoi(optarg); break;
            case '?':
            default: usage_exit(opts.bin);
        }
    }

    /* Check that input is specified. */
    if (optind + 2 > argc) {
        fprintf(stderr, "Missing input files\n");
        // usage_exit(opts.bin);
    } else {
        opts.insert = argv[optind];
        opts.search = argv[optind + 1];
    }

    return opts;
}

int main(int argc, char *argv[]) {
    Options opts = load_options(argc, argv);
    HT ht = create_table(opts);

    hash_print(ht, stdout);

    return 0;
}

static void read_data(HT ht, char *insert) {
    FILE *file = fopen(insert, "r");
    assert(file != NULL);

    #define BUFF_SIZE 128   // max length of key in ascii chars
    char buff[BUFF_SIZE];
    while (fgets(buff, BUFF_SIZE, file) != NULL) {
        sscanf(buff, KEY_PRINT_FORMAT, &key);
        hash_insert(ht, key);
    }

    fclose(file);
}

static HT create_table(Options opts) {
    unsigned int size = next_prime(2 * opts.size + 1);

    Print print = opts.string ? (Print) str_print   : (Print)   int_print;
    Eq    eq    = opts.string ? (Eq)    str_eq      : (Eq)      int_eq;

    HT ht = NULL;
    switch (opts.method) {
        case ARRAY:
            ht = opts.MTF
                ? new_hash_array_MTF(size, bad_hash, eq, print)
                : new_hash_array(size, bad_hash, eq, print);
            break;
        case LIST:
            ht = opts.MTF
                ? new_hash_list_MTF(size, bad_hash, eq, print)
                : new_hash_list(size, bad_hash, eq, print);
            break;
        case DOUBLE:
            ht = new_hash_double(size, bad_hash, bad_hash, eq, print);
            break;
        case LINEAR:
            ht = new_hash_linear(size, bad_hash, eq, print);
            break;
        default:
            fprintf(stderr, "Invalid collision resolution method\n");
            exit(EXIT_FAILURE);
    }

    return ht;
}
