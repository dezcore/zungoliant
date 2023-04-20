#include "./../include/file.h"
#define STR_LEN 100

int getCurrentDir(char *res,  size_t size) {
    int state = 0;
    if(getcwd(res, size) != NULL) {
       //printf("Current working dir: %s\n", res);
       state = 1;
    } else {
       perror("getcwd() error");
    }

    return state;
}

int existFile(char *fileName) {
    int exist = 0;
    if(fileName != NULL && access(fileName, F_OK) == 0)
        exist = 1;

    return exist;
}

int printContent(char *filePath) {
    FILE *fptr;
    char* line;

    if(filePath == NULL) exit(EXIT_FAILURE);
    line = malloc(STR_LEN * sizeof(char*));
    fptr = fopen(filePath, "r");
    
    if(fptr == NULL) exit(EXIT_FAILURE);

    while(fgets(line, STR_LEN, fptr)) {
        printf("%s\n", line);
    }
    
    free(line);
    fclose(fptr);
    return 0; 
}
