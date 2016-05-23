#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

#include "extra.h"

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s (-n size | d n | c n)\n", bin);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int c, size = 0, exp, act;
    while ((c = getopt(argc, argv, "n:")) != -1) {
        switch (c) {
            case 'n':
                size = atoi(optarg);
                exp = next_prime(2 * size + 1);
                act = determine_size(size);
                if (exp != act) {
                    fprintf(stderr, "Expected: %d, Actual: %d", exp, act);
                    exit(EXIT_FAILURE);
                }
                return 0;
            case 'd':
            case 'c':
            default: usage_exit(argv[0]);
        }
    }
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
