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
    char *first_pattern = "var ytInitialData = ";//"/.+=./";
    char *second_pattern = ";";//";$"
    char *filePath = (char*) malloc(STR_SIZE * sizeof(char));
    char *saveFilePath = (char*) malloc(STR_SIZE * sizeof(char));
    char* fileContent = (char*) malloc(sizeof(char));
    
    struct json_object *new_obj;
    struct json_object_iterator it;
	struct json_object_iterator itEnd;
    
    
    


    getCurrentDir(filePath, STR_SIZE);
    getCurrentDir(saveFilePath, STR_SIZE);
    strcat(filePath, "/data/file/ytInitialData_regex");
    strcat(saveFilePath, "/data/file/test_regex");
    fileContent = load_file(filePath, fileContent);

    regex_replace(&fileContent, first_pattern, rpl);
    regex_replace(&fileContent, second_pattern, rpl);
    
    it = json_object_iter_init_default();
    new_obj = json_tokener_parse(fileContent);
    it = json_object_iter_begin(new_obj);
	itEnd = json_object_iter_end(new_obj);
    
    while(!json_object_iter_equal(&it, &itEnd)) {
		printf("%s\n", json_object_iter_peek_name(&it));
		printf("%s\n", json_object_to_json_string(json_object_iter_peek_value(&it)));
		json_object_iter_next(&it);
	}

    //appendStrToFile(saveFilePath, fileContent);
    json_object_put(new_obj);

    free(filePath);
    free(fileContent);
    free(saveFilePath);
    return 0;
}