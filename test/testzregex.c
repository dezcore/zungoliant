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
    char *pattern = "\\[([^-]+)->([^]]+)\\]";
    char *str = strdup("before [link->address] some text [link2->addr2] trail");
    char rpl[] = "<a href=\"\2\">\1</a>";
    puts(str);
    regex_replace(&str, pattern, rpl);
    puts(str);
    free(str);
    return 0;
}