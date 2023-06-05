#include "./../include/fifo.h"

int init_file_struct(File *file) {
    if(file != NULL) {
        file->size = 0;
        file->head = NULL;
    }
    return 0;
}

int fifo_init(File *fifo) {
    if(fifo != NULL) {
        fifo->size = 0;
        fifo->head = NULL;
    }
    return 0;
}

int init_yfile(Yfile *file) {
    if(file != NULL) {
        file->size = 0;
        file->head = NULL;
    }
    return 0;
}

size_t size(File *file) {
    if(file == NULL) exit(EXIT_FAILURE);
    return (file->size);
}

size_t y_file_size(Yfile *file) {
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

int push_ydata(Yfile **file, const char *title, const char *img, const char *videoId) {
    Ydata *data, *current;
    if(file == NULL) exit(EXIT_FAILURE);

    data = malloc(sizeof(*data));
    data->title = malloc((strlen(title)+1) * sizeof(char));
    data->img = malloc((strlen(img)+1) * sizeof(char));
    data->videoId = malloc((strlen(videoId)+1) * sizeof(char));
    data->next = NULL;
    
    stpcpy(data->title, title);
    stpcpy(data->img, img);
    stpcpy(data->videoId, videoId);

    if((*file)->head != NULL) {
        current = (*file)->head;

        while(current->next != NULL) {
            current = current->next;
        }
        current->next = data;
        (*file)->size = (*file)->size + 1;
    } else {
        (*file)->head = data;
        (*file)->size = (*file)->size + 1;
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

int pop_yfile(Yfile **file, Ydata **data) {

    if(file == NULL) exit(EXIT_FAILURE);

    if((*file)->head != NULL) {
        (*data) = (*file)->head;
        (*file)->head = (*data)->next;
        --((*file)->size);
    }

    return 0;
}

int displayElement(Element *element) {
    if(element == NULL) exit(EXIT_FAILURE);
     printf("%s\n", element->value);
    return 0;
}

int print_ydata(Ydata *data) {
    if(data == NULL) exit(EXIT_FAILURE);
    printf("(%s, %s, %s)\n", data->title, data->img, data->videoId);
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

int print_yfile(Yfile *file) {   
    if(file == NULL) exit(EXIT_FAILURE);
    Ydata *current = file->head;

    printf("[\n");
    while(current != NULL) {
        print_ydata(current);
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

int free_ydata(Ydata *data) {
    if(data != NULL) {
        free(data->title);
        free(data->img);
        free(data->videoId);
        data->next = NULL;
        free(data);
    }

    return 0;
}

int freeFile(File *file) {
    Element *current;
    Element *elementToDelete;
    
    if(file != NULL) {
        current = file->head;
        while(current != NULL) {
            elementToDelete = current;
            current = current->next;
            freeElement(elementToDelete);
        }

        file->head = NULL;
        free(file);
    }
    return 0;
}

int free_yfile(Yfile *file) {
    Ydata *current;
    Ydata *elementToDelete;

    if(file != NULL) {
        current = file->head;

        while(current != NULL) {
            elementToDelete = current;
            current = current->next;
            free_ydata(elementToDelete);
        }

        file->head = NULL;
        free(file);
    }
    
    return 0;
}