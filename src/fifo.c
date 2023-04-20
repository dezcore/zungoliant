#include "./../include/fifo.h"

File* init() {
    File *file = malloc(sizeof(*file));
    file->size = 0;
    file->head = NULL;
    return file;
}

size_t size(File *file) {
    if(file == NULL) exit(EXIT_FAILURE);
    return (file->size);
}

int push(File *file, char *value) {
    Element *element,  *current;
    int len = (int) strlen(value);
    if(file == NULL) exit(EXIT_FAILURE);

    element = malloc(sizeof(*element));
    element->value = malloc( len * sizeof(char*));
    element->next = NULL;
    stpcpy(element->value, value);
    
   
    if(file->head != NULL) {
        current = file->head;

        while(current->next != NULL) {
            current = current->next;
        }
        current->next = element;
        file->size = file->size + 1;
    } else {
        file->head = element;
        file->size = file->size + 1;
    }

    return 0;
}

Element* pop(File *file) {
    Element *element;
    if(file == NULL) exit(EXIT_FAILURE);

    if(file->head != NULL) {
        element = file->head;

        file->head = element->next;
        --(file->size);
    }

    return element;
}

int displayElement(Element *element) {
    if(element == NULL) exit(EXIT_FAILURE);
     printf("%s\n", element->value);
    return 0;
}

int display(File *file) {   
    if(file == NULL) exit(EXIT_FAILURE);
    Element *current = file->head;

    printf("[\n");
    while(current != NULL) {
        printf("%s", current->value);
        current = current->next;
        if(current != NULL) printf(",\n");
    }
    printf("\n]\n");

    return 0;
}

int freeElement(Element *element) {
    if(element != NULL) {
        free(element->value);
        element->next = NULL;
        free(element);
    }

    return 0;
}

int freeFile(File *file) {
    Element * elementToDelete;
    Element * current = file->head;

    while(current != NULL) {
        elementToDelete = current;
        current = current->next;
        freeElement(elementToDelete);
    }

    file->head = NULL;
    free(file);

    return 0;
}