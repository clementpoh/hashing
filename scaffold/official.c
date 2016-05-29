#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "official.h"

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

/* Initialise universal hash coefficients and return a pointer to them */
static int *init_universal(int len, int size);

unsigned int official_size(int n) {
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

/* Universal hash function as described in Dasgupta et al 1.5.2 */
unsigned int off_hash(unsigned char *key, unsigned int size) {
    static int *coeffs = NULL;

    if (!coeffs)
        coeffs = init_universal(MAXSTRLEN, size);

    unsigned int hash = 0;
    for (int i = 0; i < MAXSTRLEN && key[i]; i++)
        hash += coeffs[i] * key[i];

    return hash % size;
}

/* Initialise universal hash coefficients and return a pointer to them. */
static int *init_universal(int len, int size) {
    int *coeffs = calloc(MAXSTRLEN, sizeof(*coeffs));
    assert(coeffs);

    for (int i = 0; i < len; i++)
        coeffs[i] = rand() % size;

    return coeffs;
}
