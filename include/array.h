#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _ARRAY {
    char **elements;
    size_t number_of_elements;
} ARRAY;

int free_array(ARRAY *array);
int init_array(ARRAY *array, size_t number_of_elements, size_t element_size);
#endif