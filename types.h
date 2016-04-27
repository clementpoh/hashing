#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdbool.h>

/* Prints n to file */
void int_print(FILE *file, long n);

/* Returns whether n1 is equal to n2 */
bool int_eq(long n1, long n2);

/* Prints str to file */
void str_print(FILE *file, char *str);

/* Returns whether str1 is equal to str2 */
bool str_eq(char *str1, char *str2);

#endif
