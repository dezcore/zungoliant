#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

typedef struct _Element {
    char *value;
    struct _Element * next;
} Element;

typedef struct _File {
    Element * head;
    size_t size;
} File;

File* init();
size_t size(File *file);
int push(File *file, char *value);
Element* pop(File *file);
int display(File *file);
int freeFile(File *file);
int freeElement(Element *element);
int displayElement(Element *element);

#endif