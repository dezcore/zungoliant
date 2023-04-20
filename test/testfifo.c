#include "./../include/fifo.h"
#define STR_SIZE 20


int test_init() {
    printf("test_init : \n");
    File *file = init();
    display(file);
    freeFile(file);
    return 0;
}

int test_push() {
    char * str = (char *) malloc(STR_SIZE * sizeof(char*));
    char * str1 = (char *) malloc(STR_SIZE * sizeof(char*));
    char * str2 = (char *) malloc(STR_SIZE * sizeof(char*));

    File *file = init();
    strcpy(str, "Hello world !");
    strcpy(str1, "Hello world 1 !");
    strcpy(str2, "Hello world 2 !");

    push(file, str);
    push(file, str1);
    push(file, str2);

    printf("size : %lu\n", file->size);

    display(file);
    free(str);
    free(str1);
    free(str2);
    freeFile(file);
    return 0;
}

int test_pop() {
    Element *element;
    File *file = init();
    char * str = (char *) malloc(STR_SIZE * sizeof(char*));
    char * str1 = (char *) malloc(STR_SIZE * sizeof(char*));

    strcpy(str, "Hello world !");
    strcpy(str1, "Hello world 1 !");

    push(file, str);
    push(file, str1);
    printf("size : %lu\n", file->size);
    element = pop(file);
    displayElement(element);
    printf("size : %lu\n", file->size);

    free(str);
    free(str1);
    freeFile(file);
    freeElement(element);
    return 0;
}