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

#define MINCHAR 'A'
#define MAXCHAR 'z'

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

// triple for Euclid's extended algorithm
typedef struct {
    int x, y, d;
} gcd;

/* Generate coefficients from seed, print them and store them in coeffs */
static void print_universal(int len, int seed, int size, int *coeffs);

/* Generate strings len long and print n strings that hash to 0 */
static void generate(int size, int len, char *string, int i, int *n);

/* Determine the value that combined with string hashes to 0 */
static char hash_zero(int *coeffs, char *string, int size, int c);

/* Extended Euclidean algorithm */
static gcd extended_euclid(int a, int b);

/* Recursive call of extended Euclidean algorithm*/
static gcd euclid(int a, int b);

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    return n < 2 ? 2 : next_prime(2 * n + 1);
}

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n) {
    n = n % 2 ? n : n + 1;

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

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
    char string[MAXSTRLEN] = { '\0' };
    int coeffs[MAXSTRLEN];

    print_universal(MAXSTRLEN, seed, size, coeffs);
    for (int len = 1; len < MAXSTRLEN && n > 0; len++) {
        generate(size, len, string, 0, &n);
    }
}

/* Generate coefficients from seed, print them and store them in coeffs */
static void print_universal(int len, int seed, int size, int *coeffs) {
    // Print the number of coefficients
    printf("%d\n", len);

    // Reseed the randon number generator
    srand(seed);
    for (int i = 0; i < len; i++) {
        coeffs[i] = rand() % size;
        printf("%d\n", (unsigned char) coeffs[i]);
    }
}

/* Generate strings len long and print n strings that hash to 0
 * Referenced: http://codereview.stackexchange.com/q/38474 */
static void generate(int size, int len, char *string, int i, int *n) {
    // Constrain characters between A and z
    // to allow all characters: (char c = 1; c > 0 && *n > 0; c++)
    for (unsigned char c = MINCHAR; c <= MAXCHAR && *n > 0; c++) {
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
void collide_clever(unsigned int size, unsigned int seed, int n) {
    char string[MAXSTRLEN] = { '\0' };
    int coeffs[MAXSTRLEN];
    int len, c;

    if (size > next_prime(UCHAR_MAX)) {
        fprintf(stderr, "%d exceeds limit: %d\n", size, next_prime(UCHAR_MAX));
        exit(EXIT_FAILURE);
    }

    print_universal(MAXSTRLEN, seed, size, coeffs);

    // Find the position of the first non-zero universal coefficient
    for (c = 0; !coeffs[c]; c++);

    for (int i = 0; i < n; i++) {
        // Generate a random string at least MINLEN long
        len = rand() % (MAXSTRLEN - MINLEN) + MINLEN;
        string[len] = '\0';

        // Constrain the characters to between A to z
        for(int j = 0; j < len; j++)
            string[j] = rand() % (MAXCHAR - MINCHAR) + MINCHAR;

        // Find a value of string[c] so that string hashes to zero
        string[c] = hash_zero(coeffs, string, size, c);

        printf("%s\n", string);
    }
}

/* Determine the value that combined with string hashes to 0 */
static char hash_zero(int *coeffs, char *string, int size, int c) {
    gcd euclid = extended_euclid(size, coeffs[c]);

    // euclid.y + size to ensure it's positive
    euclid.y = (euclid.y + size) % size;

    // Get the hash of string excluding the char at c
    int hash = universal_hash((unsigned char*)string, size);
    hash -= coeffs[c] * (unsigned char) string[c] % size;

    // size is prime so euclid.y * coeffs % size = 1
    // So hash + (size - hash) * 1 = size % size = 0
    return (size - hash) * euclid.y % size;
}

/* Extended Euclidean algorithm */
static gcd extended_euclid(int a, int b) {
    #ifndef MAX
        #define MAX(a, b) ( ((a) > (b)) ? (a) : (b) )
        #define MIN(a, b) ( ((a) < (b)) ? (a) : (b) )
    #endif
    return euclid(MAX(a, b), MIN(a, b));
}

/* Recursive call of extended Euclidean algorithm */
static gcd euclid(int a, int b) {
    if (!b) return (gcd) { 1, 0, a };

    gcd e = euclid(b, a % b);
    return (gcd) { e.y, e.x - (a / b) * e.y, e.d };
}
