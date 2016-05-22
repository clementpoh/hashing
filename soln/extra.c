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

#define MAXSTRLEN 256
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
 * print them and store them in coeffs */
static void get_coefficients(int len, int seed, int size, char *coeffs);

/* Extended Euclidean algorithm */
static gcd extended_euclid(int a, int b);

/* Recursive call of extended Euclidean algorithm*/
static gcd euclid(int a, int b);

/* Determine the char that when combined with str will hash to 0 */
static char hash_zero(char *coeffs, char *str, int size);

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
 * print them and store them in coeffs */
static void get_coefficients(int len, int seed, int size, char *coeffs) {
    // Print the number of coefficients
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
static void generate(int size, int len, char *string, int i, int *n) {
    // Constrain characters between A and z
    // to allow all characters: (char c = 1; c > 0 && *n > 0; c++)
    for (unsigned char c = 'A'; c <= 'z' && *n > 0; c++) {
        string[i] = c;

        if (i == len - 1) {
            if (!universal_hash((unsigned char*) string, size)) {
                printf("%s\n", string);
                if (!--*n) break;
            }
        } else generate(size, len, string, i + 1, n);
    }
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
    char string[MAXSTRLEN] = { '\0' };
    char coeffs[MAXSTRLEN];

    get_coefficients(MAXSTRLEN, seed, size, coeffs);
    for (int len = 1; len < MAXSTRLEN && n > 0; len++) {
        generate(size, len, string, 0, &n);
    }
}

/* Extended Euclidean algorithm */
static gcd extended_euclid(int a, int b) {
    #ifndef MAX
        #define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
        #define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
    #endif
    return euclid(MAX(a, b), MIN(a, b));
}

/* Recursive call of extended Euclidean algorithm */
static gcd euclid(int a, int b) {
    if (!b) return (gcd) { 1, 0, a };

    gcd e = euclid(b, a % b);
    return (gcd) { e.y, e.x - (a / b) * e.y, e.d };
}

/* Replicates the universal hash of string. Can't call universal hash directly
 * because of coefficient offset */
static int replicate_hash(char *string, char *coeffs, int size) {
    int hash = 0;

    for (int i = 0; i < MAXSTRLEN && string[i]; i++)
        hash += coeffs[i] * string[i];

    return hash % size;
}

static char hash_zero(char *coeffs, char *str, int size) {
    gcd euclid = extended_euclid(size, coeffs[0]);

    // euclid.y + size to ensure it's positive
    euclid.y = (euclid.y + size) % size;

    // Replicate the universal_hash from the str + 1
    int hash = replicate_hash(str + 1, coeffs + 1, size);

    int y = (euclid.y * (size - hash) / euclid.d) % size;

    return y + size * (1 + ('A' - y) / size);
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed
 * Assumes the first universal hash coefficient is non-zero */
void collide_clever(unsigned int size, unsigned int seed, int n) {
    char string[MAXSTRLEN] = { '\0' };
    char coeffs[MAXSTRLEN];
    int len, c = 0;

    if (size > UCHAR_MAX) {
        fprintf(stderr, "%d exceeds the allowable hash size: %d\n", size, UCHAR_MAX);
        exit(EXIT_FAILURE);
    }

    get_coefficients(MAXSTRLEN, seed, size, coeffs);
    for (int i = 0; i < n; i++) {
        // Generate a random string
        len = rand() % (MAXSTRLEN - MINLEN) + MINLEN;
        string[len] = '\0';

        // Constrain the characters to between A to z
        for(int j = 0; j < len; j++)
            string[j] = rand() % ('z' - 'A') + 'A';

        // string[c] now hashes to zero
        string[c] = hash_zero(coeffs, string, size);

        printf("%2d %s\n", universal_hash((unsigned char *)string, size), string);
    }
}
