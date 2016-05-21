/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module is for the implementation of tasks specific to assignment 2
 *
*/
#include "extra.h"
#include "hash.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 256
#define MAX_TRY 10
#define MIN_PRINTABLE   33
#define MAX_PRINTABLE   126

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    return next_prime(2 * n + 1);
}

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n) {
    n = n % 2 ? n : n + 1;

    while (!is_prime(n)) {
        n = n + 2;
    }

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

static void print_coefficients(int len, unsigned int seed, unsigned int size) {
    srand(seed);
    printf("size: %d\n", len);
    for (int i = 0; i < len; i++) {
        printf("%d: %d\n", i, rand() % size);
    }
}

/* Generate strings len long and print the ones that hash to 0
 * Stop when n reaches 0
 * Referenced: http://codereview.stackexchange.com/q/38474
 * */
static void generate(int size, int len, unsigned char *string, int i, int *n) {
    for (unsigned char c = 1; c > 0 && *n > 0; c++) {
        string[i] = c;

        if (i == len - 1) {
            if (!universal_hash(string, size)) {
                printf("%s\n", string);
                if (!--*n) break;
            }
        } else generate(size, len, string, i + 1, n);
    }
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
    unsigned char string[MAXSTRLEN] = { '\0' };

    print_coefficients(MAXSTRLEN, seed, size);
    for (int len = 1; len < MAXSTRLEN && n > 0; len++) {
        generate(size, len, string, 0, &n);
    }
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n) {
}
