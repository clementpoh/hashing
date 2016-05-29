#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdbool.h>

#define MAXSTRLEN 256

/* Official implementations of functions */
unsigned int official_size(int size);

/* Returns a copy of src */
bool off_eq(char *str1, char *str2);

/* Returns a copy of src */
char *off_copy(char *str);

/* Prints str to file */
void off_print(FILE *file, char *str);

/* Universal hash function as described in Dasgupta et. al 1.5.2 */
unsigned int off_hash(unsigned char *key, unsigned int size);

#endif
