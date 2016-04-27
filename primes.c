#include "primes.h"


#include <stdio.h> // TODO: REMOVE ME

#include <stdbool.h>

static bool is_prime(int n);

/* Return the next prime greater than or equal to n */
unsigned int next_prime(unsigned int n) {
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

