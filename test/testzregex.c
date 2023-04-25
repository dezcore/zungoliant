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

int test_getObj_rec(char* fileContent) {
    const char *value;
    struct json_object *json, *results;
    char *saveFilePath = getAbsolutePath("/data/file/test_regex");

    if(fileContent != NULL) {
        json = getJson(fileContent);

        if(json != NULL) {
            results = getObj_rec(json, "/contents/twoColumnWatchNextResults/secondaryResults/secondaryResults/results");
            
            if(results != NULL) {
                value = json_object_to_json_string_ext(results, JSON_C_TO_STRING_PRETTY);
                
                if(value != NULL) {
                    appendStrToFile(saveFilePath, value);
                }
            }

            json_object_put(json);
        }
    }

    free(saveFilePath);
    return 0;
}

int test_regex_replace() {
    char rpl[] = " ";
    char *contents = (char*) malloc(sizeof(char));
    char *patterns[] = {"var ytInitialData = ", ";"}; //"/.+=./"; , ";$"
    char *fileContent = (char*) malloc(sizeof(char));
    char *filePath = getAbsolutePath("/data/file/ytInitialData_regex");

    fileContent = load_file(filePath, fileContent);

    for(int i = 0; i < 2; i++) {
        regex_replace(&fileContent, patterns[i], rpl);
    }

    test_getObj_rec(fileContent);

    free(contents);
    free(filePath);
    free(fileContent);
    return 0;
}