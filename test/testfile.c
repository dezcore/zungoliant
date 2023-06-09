#include "./../include/fifo.h"
#include "./../include/curl.h"
#include "./../include/parser.h"
#include "./../include/testfile.h"
#define STR_SIZE 100

int test_printContent() {
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    getCurrentDir(filePath, STR_SIZE);
    strcat(filePath, "/data/file/test");
    printContent(filePath);
    free(filePath);
    return 0;
}

int test_filetoFifo() {
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    File *file = malloc(sizeof(*file));

    init_file_struct(file);
    getCurrentDir(filePath, STR_SIZE);
    strcat(filePath, "/data/file/test");
    fileToFifo(filePath, file);
    display(file);
    free(filePath);
    freeFile(file);
    
    return 0;
}

int test_createFile() {
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    getCurrentDir(filePath, STR_SIZE);
    strcat(filePath, "/data/file/test1");
    createFile(filePath);
    free(filePath);
    return 0;
}

int test_downloadPage() {
    Element *element;
    File *file = malloc(sizeof(*file));
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    char *urlsFile = (char*) malloc(STR_SIZE * sizeof(char));

    getCurrentDir(filePath, STR_SIZE);
    getCurrentDir(urlsFile, STR_SIZE);
    strcat(urlsFile, "/data/file/test");
    strcat(filePath, "/data/file/test.html");
    createFile(filePath);

    init_file_struct(file);
    fileToFifo(urlsFile, file);
    element = pop(file);

    if(element != NULL) {
        displayElement(element);
        downloadPage(&element->value, filePath);
    }
    
    free(filePath);
    free(urlsFile);
    freeFile(file);
    freeElement(element);
    return 0;
}

int test_parseFile() {
    Element *element;
    File *file = malloc(sizeof(*file));
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    char *urlsFile = (char*) malloc(STR_SIZE * sizeof(char));

    getCurrentDir(filePath, STR_SIZE);
    getCurrentDir(urlsFile, STR_SIZE);
    strcat(urlsFile, "/data/file/test");
    strcat(filePath, "/data/file/model2.html");
    createFile(filePath);

    init_file_struct(file);
    fileToFifo(urlsFile, file);
    element = pop(file);

    if(element != NULL) {
        displayElement(element);
        //downloadPage(element->value, filePath);
        parseYFile(filePath);
    }

    free(filePath);
    free(urlsFile);
    freeFile(file);
    freeElement(element);
    return 0;
}

int test_appendStrToFile() {
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    getCurrentDir(filePath, STR_SIZE);
    strcat(filePath, "/data/file/append");
    appendStrToFile(filePath, "This is testing for fprintf...\n");
    appendStrToFile(filePath,  "This is testing for fputs...\n");
    free(filePath);
    return 0;
}

int test_loadFile() {
    char* fileContent = (char*) malloc(sizeof(char));
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    getCurrentDir(filePath, STR_SIZE);
    strcat(filePath, "/data/file/model2.html");
    load_file(filePath, &fileContent);
    //printf("content : %s\n", fileContent);
    free(filePath);
    free(fileContent);
    return 0;
}