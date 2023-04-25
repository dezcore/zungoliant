#include "./../include/testzregex.h"
#define STR_SIZE 100

int test_load() {
    char* fileContent = (char*) malloc(sizeof(char));
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    getCurrentDir(filePath, STR_SIZE);
    strcat(filePath, "/data/file/model2.html");
    fileContent = load_file(filePath, fileContent);
    //printf("content : %s\n", fileContent);
    free(filePath);
    free(fileContent);
    return 0;
}

int test_regex_replace() {
    char rpl[] = " ";
    char *patterns[] = {"var ytInitialData = ", ";"}; //"/.+=./"; , ";$"
    char *fileContent = (char*) malloc(sizeof(char));
    char *saveFilePath = getAbsolutePath("/data/file/test_regex");
    char *filePath = getAbsolutePath("/data/file/ytInitialData_regex");

    fileContent = load_file(filePath, fileContent);

    //regex_replace(&fileContent, first_pattern, rpl);
    //regex_replace(&fileContent, second_pattern, rpl);
    regex_replace_all(&fileContent, patterns, 2, rpl);
    //appendStrToFile(saveFilePath, fileContent);
    
    free(filePath);
    free(fileContent);
    free(saveFilePath);
    return 0;
}