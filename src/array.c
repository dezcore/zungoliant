#include "./../include/array.h"

int print_array(ARRAY *array) {
    if(array != NULL) {
        printf("[");
        for(int i = 0; i < array->length; i++) {
            if(array->elements[i] != NULL) {
                printf("%s\n", array->elements[i]);
            }
        }
        printf("]\n");
    }
    return 0;
}

int init_array(ARRAY **array, size_t length, size_t element_size, char *defaultValue) {
    *array = malloc(sizeof(*array));
    
    if(*array != NULL) {
        (*array)->elements = malloc(length * sizeof(char*));
        for(int i = 0; i < length; i++) {
            (*array)->elements[i] = (char*) calloc(element_size, sizeof(char));
            if((*array)->elements[i] != NULL && defaultValue != NULL) {
                sprintf((*array)->elements[i], "%s", defaultValue);
            }
        }
        (*array)->length = length;
    }

    return 0;
}

int add_value(ARRAY **array, char *value, int index) {
    if(*array != NULL) {
        (*array)->elements[index] = (char*) realloc((*array)->elements[index], (strlen(value)+1) * sizeof(char));
        if((*array)->elements[index] != NULL) {
            sprintf((*array)->elements[index], "%s", value);
        } 
    }

    return 0;
}

int free_array(ARRAY *array) {
    if(array != NULL) {
        for(int i = 0; i < array->length; i++) {
            if(array->elements[i] != NULL) {
                free(array->elements[i]);
            }
        }
        free(array->elements);
        free(array);
    }

    return 0;
}