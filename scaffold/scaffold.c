#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "extra.h"
#include "hash.h"
#include "hashtable.h"

/* Tests the linear_probe hash function */
static bool test_probing(void);

/* Tests the determine_size function */
static bool test_size(int size);

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

/* Official implementations of string functions */
bool off_eq(char *str1, char *str2);
char *off_copy(char *str);
void off_print(FILE *file, char *str);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s (-n size | -l | -d n | -c n)\n", bin);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int c;
    while ((c = getopt(argc, argv, "ln:")) != -1) {
        switch (c) {
            case 'l':
                return test_probing();
            case 'n':
                return test_size(atoi(optarg));
            case 'd':
            case 'c':
            default: usage_exit(argv[0]);
        }
    }
}

/* Returns whether str1 is equal to str2 */
bool off_eq(char *str1, char *str2) {
    return !strcmp(str1, str2);
}

/* Returns a copy of src */
char *off_copy(char *src) {
    /* Remove the newline as required */
    src[strcspn(src, "\n")] = '\0';
    /* Malloc enough space for the null byte */
    char *dest = malloc(sizeof(*dest) * strlen(src) + 1);
    assert(dest);
    return strcpy(dest, src);
}

/* Prints str to file */
void off_print(FILE *file, char *str) {
    fprintf(file, " %s", str);
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
    return 0;
}

static bool test_size(int size) {
    int expect = next_prime(size);
    int actual = determine_size(size);
    if (expect != actual) {
        fprintf(stderr, "Expected: %d, Actual: %d", expect, actual);
        return EXIT_FAILURE;
    }
    return 0;
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
