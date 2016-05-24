#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

#include "extra.h"
#include "hash.h"

/* Return the next prime greater than or equal to n */
static unsigned int next_prime(unsigned int n);

/* Determine whether n is prime. */
static bool is_prime(int n);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s (-n size | -l | -d n | -c n)\n", bin);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int c, size = 0;
    while ((c = getopt(argc, argv, "ln:")) != -1) {
        switch (c) {
            case 'l':
                for (long i = 0; i < 100; i++) {
                    int h = linear_probe((void *)i, i);
                    if (h != 1) {
                        fprintf(stderr, "Expected: 1, Actual: %d", h);
                        exit(EXIT_FAILURE);
                    }
                }
                return 0;
            case 'n':
                size = atoi(optarg);
                int exp = next_prime(size);
                int act = determine_size(size);
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
