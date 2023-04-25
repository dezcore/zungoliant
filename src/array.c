#include "./../include/array.h"

int init_array(ARRAY *array, size_t number_of_elements, size_t element_size) {
    array->elements = malloc(number_of_elements * sizeof(char*));
    array->number_of_elements = number_of_elements;

    for(int i = 0; i < number_of_elements; i++) {
        array->elements[i] = malloc((element_size + 1) * sizeof(char));
        sprintf(array->elements[i], "%s", "");
    }

    return 0;
}

int free_array(ARRAY *array) {
    if(array != NULL) {
        for(int i = 0; i < array->number_of_elements; i++) {
            free(array->elements[i]);
        }
        free(array->elements);
    }
    return 0;
}