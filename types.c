
#include "types.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

static char *safe_copy(char *src);

bool int_eq(long e1, long e2) {
    return e1 == e2;
}

void int_print(FILE *file, long e) {
    fprintf(file, " %ld", e);
}

bool str_eq(char *str1, char *str2) {
    return !strcmp(str1, str2);
}

char *str_parse(char *str) {
    return safe_copy(str);
}

void str_print(FILE *file, char *str) {
    fprintf(file, " %s", str);
}

/* Returns a copy of src */
static char *safe_copy(char *src) {
    /* Remove the newline as required */
    src[strcspn(src, "\n")] = '\0';
    /* Malloc enough space for the null byte */
    char *dest = malloc(sizeof(*dest) * strlen(src) + 1);
    assert(dest);
    return strcpy(dest, src);
}

