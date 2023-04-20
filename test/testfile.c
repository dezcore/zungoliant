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