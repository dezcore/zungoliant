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
    const char *value;
    struct json_object *json, *results;
    char *contents = (char*) malloc(sizeof(char));
    char *patterns[] = {"var ytInitialData = ", ";"}; //"/.+=./"; , ";$"
    
    //char *results[] = {"contents", "twoColumnWatchNextResults", "secondaryResults", "secondaryResults", "results"};

    char *fileContent = (char*) malloc(sizeof(char));
    char *saveFilePath = getAbsolutePath("/data/file/test_regex");
    char *filePath = getAbsolutePath("/data/file/ytInitialData_regex");

    fileContent = load_file(filePath, fileContent);

    for(int i = 0; i < 2; i++) {
        regex_replace(&fileContent, patterns[i], rpl);
    }

    json = getJson(fileContent);
    results =  getObj_rec(json, "contents/twoColumnWatchNextResults/secondaryResults/secondaryResults/results");

    if(results != NULL) {
        value = json_object_to_json_string_ext(results, JSON_C_TO_STRING_PRETTY);
        printf("value : %s\n", value);
        if(value != NULL) {
            appendStrToFile(saveFilePath, value);
        }
        json_object_put(results);
    }
    //getValue(json, "contents", &contents);
    //appendStrToFile(saveFilePath, contents);

    json_object_put(json);
    free(contents);
    free(filePath);
    free(fileContent);
    free(saveFilePath);
    return 0;
}