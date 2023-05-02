#include "./../include/file.h"
#define STR_LEN 100


char* load_file(const char* filename,  char *fileContent) {
    long size;
    size_t nread;
    //char *fileContent;
    FILE *fh = fopen(filename, "rb");

    if(fh == NULL) {
        fprintf(stderr, "Can't open html file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if(fseek(fh, 0L, SEEK_END) != 0) {
        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size = ftell(fh);

    if(fseek(fh, 0L, SEEK_SET) != 0) {
        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if(size <= 0) {
        fprintf(stderr, "Can't get file size or file is empty: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    //fileContent = (char*)malloc(size + 1);
    fileContent = (char*)realloc(fileContent, size + 1);

    if(fileContent == NULL) {
        fprintf(stderr, "Can't allocate mem for html file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    nread = fread(fileContent, 1, size, fh);
    
    if(nread != size) {
        exit(EXIT_FAILURE);
    }

    fclose(fh);
    return fileContent;
}

int createFile(char *fileName) {
    FILE *fptr;
    fptr = fopen(fileName, "rb+");

    if(fptr == NULL) {  //if file does not exist, create it
        fptr = fopen(fileName, "wb");
    }

    fclose(fptr);
    return 0;
}

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

char* getAbsolutePath(const char *path) {
    char *filePath = NULL;

    if(path != NULL) {
        filePath = (char*) malloc(STR_LEN * sizeof(char));
        getCurrentDir(filePath, STR_LEN);
        strcat(filePath, path);
    }

    return filePath;
}

int get_absolutePath(const char *path, char **filePath) {
    if(path != NULL) {
        *filePath = (char*) malloc(STR_LEN * sizeof(char));
        getCurrentDir(*filePath, STR_LEN);
        strcat(*filePath, path);
    }

    return 0;
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
    
    line =(char *) malloc(STR_LEN * sizeof(char));
    fptr = fopen(filePath, "r");
    
    if(fptr == NULL) exit(EXIT_FAILURE);

    while(fgets(line, STR_LEN, fptr)) {
        printf("%s\n", line);
    }
    
    free(line);
    fclose(fptr);
    return 0; 
}

int fileToFifo(char *filePath, File *file) {
    char* line;
    FILE * fptr = fopen(filePath, "r");
    
    if(fptr != NULL) {
        line =(char *) malloc(STR_LEN * sizeof(char));

        while(fgets(line, STR_LEN, fptr)) {
            push(file, line);
        }

        free(line);
        fclose(fptr);
    } else {
        exit(EXIT_FAILURE);
    }

    return 0;
}

int appendStrToFile(char *fileName,const char* str) {
    FILE *fptr;
    fptr = fopen(fileName, "a");
    
    if(fptr!= NULL) {
        //fprintf(fptr, "This is testing for fprintf...\n");
        fputs(str, fptr);
    }
    fclose(fptr);
    return 0;
}

int createDir(char *dir_path) {
    struct stat st = {0};

    if(dir_path != NULL) {
        if(stat(dir_path, &st) == -1) {
            mkdir(dir_path, 0777);
        }
    }
    
    return 0;
}