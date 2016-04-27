
#include "types.h"

#include <string.h>

void int_print(FILE *file, long e) {
    fprintf(file, " %ld", e);
}

bool int_eq(long e1, long e2) {
    return e1 == e2;
}

void str_print(FILE *file, char *str) {
    fprintf(file, " %s", str);
}

bool str_eq(char *str1, char *str2) {
    return !strcmp(str1, str2);
}
