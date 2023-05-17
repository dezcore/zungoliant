#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct _ARRAY {
    char **elements;
    size_t length;
} ARRAY;

int free_array(ARRAY *array);
int print_array(ARRAY *array);
int add_value(ARRAY **array, char *value, int index);
int init_array(ARRAY **array, size_t length, size_t element_size, char *defaultValue);
#endif