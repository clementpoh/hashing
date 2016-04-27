#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>

#include "primes.h"
#include "hash.h"
#include "types.h"
#include "hashtable.h"

#define DEFAULT_BUCKETS 11

/* Struct to store the configuration options from the command line */
typedef struct {
    char *bin;
    char *insert;
    char *search;
    Hash hash;
    bool MTF;
    unsigned int size;
    int seed;
    bool string;
    Collision method;
} Options;

/* Print usage message and exit */
static void usage_exit(char *bin);

/* Load the the command line options into opts */
static Options load_options(int argc, char *argv[]);

static HT create_table(Options opts);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s <table> [options] insert.in search.in\n", bin);
    fprintf(stderr, "<table>\n");
    fprintf(stderr, "  a    Separate chaining with an array\n");
    fprintf(stderr, "  c    Separate chaining with a linked list\n");
    fprintf(stderr, "  d    Open addressing with double hashing\n");
    fprintf(stderr, "  l    Open addressing with linear probing\n");
    fprintf(stderr, "insert.in  File containing values to be inserted\n");
    fprintf(stderr, "search.in  File containing values to be searched\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -m       Move-to-front for separate chaining\n");
    fprintf(stderr, "  -s seed  Random seed\n");
    fprintf(stderr, "  -h hash  hash function\n");
    fprintf(stderr, "  -n size  Expected input size\n");
    fprintf(stderr, "  -t s     Expect strings as input\n");

    exit(EXIT_FAILURE);
}

/* Load the the command line options into opts */
static Options load_options(int argc, char *argv[]) {
    extern char *optarg;
    extern int optind;
    int c;
    Options opts = {
        .bin    = argv[0],
        .size   = DEFAULT_BUCKETS,
        .insert = NULL,
        .search = NULL,
        .method = LIST,
        .MTF    = false,
        .string = false,
        .seed   = 0,
        .hash   = worst_hash,
    };

    while ((c = getopt(argc, argv, "h:mn:s:t:")) != -1) {
        switch (c) {
            case 'h':
                switch (atoi(optarg)) {
                    case 1:
                        opts.hash = (Hash) bad_hash;
                        printf("Hashing: bad hash\n");
                        break;
                    case 2:
                        opts.hash = (Hash) basic_hash;
                        printf("Hashing: basic hash\n");
                        break;
                    case 3: opts.hash = (Hash) universal_hash;
                        printf("Hashing: universal hash\n");
                        break;
                    case 0:
                    default:
                        opts.hash = (Hash) worst_hash;
                        printf("Hashing: worst hash\n");
                }
                break;
            case 'm':
                opts.MTF = true;
                break;
            case 'n':
                opts.size = atoi(optarg);
                break;
            case 's':
                opts.seed = atoi(optarg);
                break;
            case 't':
                opts.string = optarg[0] == 's';
                break;
            case '?':
            default: usage_exit(opts.bin);
        }
    }

    /* Check that input is specified. */
    if (optind + 1 > argc) {
        fprintf(stderr, "Missing collision resolution method\n");
        usage_exit(opts.bin);
    }

    if (optind + 2 > argc) {
        fprintf(stderr, "Missing input keys\n");
        // usage_exit(opts.bin);
    }
    
    if (optind + 3 > argc) {
        fprintf(stderr, "Missing search keys\n");
        // usage_exit(opts.bin);
    }

    switch (argv[optind][0]) {
        case 'a': opts.method = ARRAY;      break;
        case 'c': opts.method = LIST;       break;
        case 'd': opts.method = DOUBLE;     break;
        case 'l': opts.method = LINEAR;     break;
        default: usage_exit(opts.bin);
    }

    // opts.insert = argv[optind + 1];
    // opts.search = argv[optind + 2];

    return opts;
}

int main(int argc, char *argv[]) {
    Options opts = load_options(argc, argv);
    HT ht = create_table(opts);

    /* Seed the random number generator */
    srand(opts.seed);

    hash_parse(ht, stdin);

    printf("Strings: %d\n", opts.string);
    hash_print(ht, stdout);

    return 0;
}

static HT create_table(Options opts) {
    unsigned int size = next_prime(2 * opts.size + 1);

    Eq    eq    = opts.string ? (Eq)    str_eq      : (Eq)      int_eq;
    Parse parse = opts.string ? (Parse) str_parse   : (Parse)   atoi;
    Print print = opts.string ? (Print) str_print   : (Print)   int_print;

    HT ht = NULL;
    switch (opts.method) {
        case ARRAY:
            ht = opts.MTF
                ? new_hash_array_MTF(size, opts.hash, eq, parse, print)
                : new_hash_array(size, opts.hash, eq, parse, print);
            break;
        case LIST:
            ht = opts.MTF
                ? new_hash_list_MTF(size, opts.hash, eq, parse, print)
                : new_hash_list(size, opts.hash, eq, parse, print);
            break;
        case DOUBLE:
            ht = new_hash_double(size, opts.hash, opts.hash, eq, parse, print);
            break;
        case LINEAR:
            ht = new_hash_linear(size, opts.hash, eq, parse, print);
            break;
        default:
            fprintf(stderr, "Invalid collision resolution method\n");
            exit(EXIT_FAILURE);
    }

    return ht;
}
