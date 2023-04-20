#include "./../include/testfile.h"
#define STR_SIZE 100

int test_printContent() {
    char *filePath = malloc(STR_SIZE * sizeof(char*));

    if(filePath == NULL) exit(EXIT_FAILURE);
    strcpy(filePath, "../data/file/test");
    printContent(filePath);
    free(filePath);
    return 0;
}