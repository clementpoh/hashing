#include "types.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Returns whether n1 is equal to n2 */
bool int_eq(long e1, long e2) {
    return e1 == e2;
}

/* Prints n to file */
void int_print(FILE *file, long e) {
    fprintf(file, " %ld", e);
}

/* Returns whether str1 is equal to str2 */
bool str_eq(char *str1, char *str2) {
    return !strcmp(str1, str2);
}

/* Returns a copy of src */
char *str_copy(char *src) {
    /* Remove the newline as required */
    src[strcspn(src, "\n")] = '\0';
    /* Malloc enough space for the null byte */
    char *dest = malloc(sizeof(*dest) * strlen(src) + 1);
    assert(dest);
    return strcpy(dest, src);
}

/* Prints str to file */
void str_print(FILE *file, char *str) {
    fprintf(file, " %s", str);
}

