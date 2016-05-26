#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "extra.h"
#include "hash.h"
#include "hashtable.h"

#define SEED 1337
#define MAXSTRLEN 256

/* Tests the bad_hash function */
static bool test_bad(int seed, int n);

/* Tests the linear_probe hash function */
static bool test_probing(void);

/* Tests the determine_size function */
static bool test_size(int size);

/* Tests the collide_dumb function */
static bool test_collide(int size, int n);

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s (-b | -n size | -p | -c n)\n", bin);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int c;
    while ((c = getopt(argc, argv, "bdps:")) != -1) {
        switch (c) {
            case 'b': // Test bad hash
                return test_bad(SEED, MAXSTRLEN);
            case 'c':
                return test_collide(atoi(optarg), 2);
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
    unsigned int size = next_prime(n);

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

static bool test_collide(int size, int n) {
    int coeffs[MAXSTRLEN];
    unsigned char string[MAXSTRLEN];
    load_universal(coeffs);

    bool success = true;
    for (int i = 0; i < n; i++) {
        fgets((char *)string, MAXSTRLEN, stdin);
        string[strcspn((char *)string, "\n")] = '\0';

        success = success && !replicate_hash(coeffs, string, size); 
    }

    return !success;
}

static bool test_size(int size) {
    int expect = next_prime(size);
    int actual = determine_size(size);
    if (expect != actual) {
        fprintf(stderr, "Expected: %d, Actual: %d", expect, actual);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static bool test_probing(void) {
    const int expect = 1;
    for (long i = 0; i < 100; i++) {
        int hash = linear_probe((void *)i, i);
        if (hash != expect) {
            fprintf(stderr, "Expected: %d, Actual: %d", expect, hash);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n) {
    if (n < 2) return 2;
    n = 2 * n + 1;

    while (!is_prime(n))
        n = n + 2;

    return n;
}

/* Determine whether n is prime. */
static bool is_prime(int n) {
    if (n < 2)
        return false;

    for (int div = 2; div * div <= n; div++) {
        if (n % div == 0)
            return false;
    }
    return true;
}
