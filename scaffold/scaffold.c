#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "extra.h"
#include "hash.h"
#include "hashtable.h"

#include "official.h"

#define SEED 1337

/* Tests the bad_hash function */
static bool test_bad(int seed, int n);

/* Tests the linear_probe hash function */
static bool test_probing(void);

/* Tests the determine_size function */
static bool test_size(int size);

/* Tests the collide_function */
static bool test_collide(int size, int seed, int n);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s (-b | -c size seed n | -n size | -p )\n", bin);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int c, seed, size;
    while ((c = getopt(argc, argv, "bc:dps:")) != -1) {
        switch (c) {
            case 'b': // Test bad hash
                return test_bad(SEED, MAXSTRLEN);
            case 'c': // Test collissions
                size = official_size(atoi(optarg));
                seed = atoi(argv[optind]);
                // n = atoi(argv[optind + 1]);
                return test_collide(size, seed, 2);
            case 'p': // Test linear probing
                return test_probing();
            case 's': // Test determine_size
                return test_size(atoi(optarg));
            default: usage_exit(argv[0]);
        }
    }
}

static bool test_bad(int seed, int n) {
    srand(seed);
    unsigned int size = official_size(n);

    for (long i = 0; i < 100; i++) {
        int len = rand() % (MAXSTRLEN - 1) + 1;

        char string[MAXSTRLEN] = { '\0' };
        for (int j = 0; j < len; j++)
            string[j] = rand() % ('a' - 'z') + 'a';

        unsigned int hash = bad_hash((void *)string, size);
        if (hash > size) {
            fprintf(stderr, "Hash %d out of range: %d", hash, size);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

unsigned int replicate_hash(int *coeffs, unsigned char *string, int size) {
    unsigned int hash = 0;
    for (int i = 0; i < MAXSTRLEN && string[i]; i++) {
        hash += coeffs[i] * string[i];
    }
    return hash % size;
}

void load_universal(int *coeffs) {
    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; i++)
        scanf("%d\n", coeffs + i);
}

static bool test_collide(int size, int seed, int n) {
    int coeffs[MAXSTRLEN], replica = 0, student = 0, official = 0;
    unsigned char string[MAXSTRLEN];

    // Reseed random generator and initialise universal_hash
    srand(seed);
    universal_hash((unsigned char *)"init", size);

    // Reseed random generator and initialise universal_hash
    srand(seed);
    off_hash((unsigned char *)"init", size);

    load_universal(coeffs);
    while (fgets((char *)string, MAXSTRLEN, stdin)) {
        string[strcspn((char *)string, "\n")] = '\0';

        int repl = replicate_hash(coeffs, string, size);
        int univ = universal_hash(string, size);
        int off = off_hash(string, size);

        replica += !repl;
        student += !univ;
        official += !off;

        if (repl)
            fprintf(stderr, "hash: %3d: student: %3d official: %3d len: %3d, %s\n"
                , repl , univ , off , strlen((char *)string) , string);

    }

    fprintf(stderr, "Hashed to zero - replica: %d student: %d, official: %d\n",
            replica, student, official);
    return !(replica >= n);
}

static bool test_size(int size) {
    int expect = official_size(size);
    int actual = determine_size(size);
    if (expect != actual) {
        fprintf(stderr, "Expected: %3d, Actual: %3d", expect, actual);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static bool test_probing(void) {
    const int expect = 1;
    for (long i = 0; i < 100; i++) {
        int hash = linear_probe((void *)i, i);
        if (hash != expect) {
            fprintf(stderr, "Expected: %3d, Actual: %3d", expect, hash);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

