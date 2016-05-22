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
#include <limits.h>

#define MAXSTRLEN 32
#define MINLEN 3

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

// triple for Euclid's extended algorithm
typedef struct {
    int x, y, d;
} gcd;

/* Generate the universal hash coefficients from seed,
 * print them and store them in cs */
static void print_coeffs(int len, unsigned int seed,
        unsigned int size, unsigned char *cs);

static gcd extended_euclid(int a, int b);
static gcd euclid(int a, int b);
static unsigned char det_char(unsigned char *coeffs, gcd euclid, unsigned int size);

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

/* Generate the universal hash coefficients from seed,
 * print them and store them in cs */
static void print_coeffs(int len, unsigned int seed,
        unsigned int size, unsigned char *coeffs) {

    printf("%d\n", len);

    srand(seed);
    for (int i = 0; i < len; i++) {
        coeffs[i] = rand() % size;
        printf("%d\n", coeffs[i]);
    }
}

/* Generate strings len long and print the ones that hash to 0
 * Stop when n reaches 0
 * Referenced: http://codereview.stackexchange.com/q/38474 */
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
    unsigned char coeffs[MAXSTRLEN];

    univ_cs(MAXSTRLEN, seed, size, coeffs);
    for (int len = 1; len < MAXSTRLEN && n > 0; len++) {
        generate(size, len, string, 0, &n);
    }
}

static gcd extended_euclid(int a, int b) {
    #ifndef MAX
        #define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
        #define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
    #endif
    return euclid(MAX(a, b), MIN(a, b));
}

// Extended euclidean algorithm
static gcd euclid(int a, int b) {
    if (!b) return (gcd) { 1, 0, a };

    gcd e = euclid(b, a % b);
    return (gcd) { e.y, e.x - (a / b) * e.y, e.d };
}

static unsigned char
det_char(unsigned char *coeffs, gcd euclid, unsigned int size) {
    // euclid.y + size to make sure it's positive
    euclid.y = (euclid.y + size) % size;

    return euclid.y;
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n) {
    unsigned char string[MAXSTRLEN] = { '\0' };
    unsigned char coeffs[MAXSTRLEN];
    int len, hash, c;

    if (size > UCHAR_MAX)
        exit(EXIT_FAILURE);

    univ_cs(MAXSTRLEN, seed, size, coeffs);

    for (int i = 0; i < n; i++) {

        // Generate a random string
        len = rand() % (MAXSTRLEN - MINLEN) + MINLEN;
        string[len] = '\0';

        for(int j = 0; j < len; j++)
            string[j] = rand() % ('z' - 'A') + 'A';

        hash = universal_hash(string + 1, size);
        gcd euclid = extended_euclid(size, coeffs[c]);

        // string[c] now hashes to zero
        string[c] = det_char(coeffs, euclid, size);

        printf("c: %d, c * coeffs[c] %% size = %d\n", string[c], string[c] * coeffs[c] % size);
        printf("%2d %s\n", universal_hash(string, size), string);
    }
}
