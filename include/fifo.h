#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Element {
    char *value;
    struct _Element * next;
} Element;

typedef struct _File {
    Element * head;
    size_t size;
} File;

typedef struct _Ydata {
    char *title;
    char *img;
    char *videoId;
    struct _Ydata * next;
} Ydata;

typedef struct _Yfile {
    Ydata *head;
    int size;
} Yfile;

size_t size(File *file);
int display(File *file);
Element* pop(File *file);
int freeFile(File *file);
int fifo_init(File *fifo);
int free_ydata(Ydata *data);
int free_yfile(Yfile *file);
int init_yfile(Yfile *file);
int print_ydata(Ydata *data);
int print_yfile(Yfile *file);
size_t y_file_size(Yfile *file);
int init_file_struct(File *file);
int freeElement(Element *element);
int push(File *file, char *value);
int displayElement(Element *element);
int pop_yfile(Yfile **file, Ydata **data);
int push_ydata(Yfile **file, const char *title, const char *img, const char *videoId);
#endif