#include "./../include/file.h"
#define STR_LEN 100

int printContent(const char *filePath) {
    FILE *fptr;
    char* line;

    if(filePath == NULL) exit(EXIT_FAILURE);
    line = malloc(STR_LEN * sizeof(char*));
    fptr = fopen(filePath, "r");
    printf("test_printContent : %s\n", filePath);
    /*if(fptr == NULL) exit(EXIT_FAILURE);

    while(fgets(line, STR_LEN, fptr)) {
        printf("%s\n", line);
    }*/

    free(line);
    fclose(fptr);
    return 0; 
}
