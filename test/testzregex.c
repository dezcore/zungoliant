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
    char *saveFilePath = getAbsolutePath("/data/file/replace_regex");

    fileContent = load_file(filePath, fileContent);

    for(int i = 0; i < 2; i++) {
        regex_replace(&fileContent, patterns[i], rpl);
        //appendStrToFile(saveFilePath, fileContent);
    }

    test_getObj_rec(fileContent);

    free(contents);
    free(filePath);
    free(fileContent);
    free(saveFilePath);
    return 0;
}

int extract_htmlpagedata(char *downloadPage) {
    char *contents;
    char rpl[] = " ";
    char *saveFilePath = NULL;
    char *parseContentPath = NULL; 
    char *patterns[] = {"var ytInitialData = ", ";"}; //"/.+=./"; , ";$"

    if(downloadPage != NULL) {
        parseYFile(downloadPage);
        contents = (char*) malloc(sizeof(char));        

        get_absolutePath(TEST_YINITDATA_FILE_PATH, &parseContentPath);
        get_absolutePath(TEST_PARSE_FILE_PATH, &saveFilePath);

        if(parseContentPath != NULL && saveFilePath != NULL) {
            printf("parseContentPath : %s\n", parseContentPath);
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {
                for(int i = 0; i < 2; i++) {
                    regex_replace(&contents, patterns[i], rpl);
                }
                printf("%s, %s\n", parseContentPath, saveFilePath);
                appendStrToFile(saveFilePath, contents);
                free(contents);
            } else {
                printf("Empty content (extract_htmlpagedata)\n");
            }

            free(saveFilePath);
            free(parseContentPath);
        }

        //free(saveFilePath);
        //free(parseContentPath);
    }

    return 0;
}

int test_downloadPage_and_replace() {
    Element *url = NULL; 
    File *urls_fifo = init();
    char *urlsFileSrc =  NULL;
    char *downloadPageSrc = NULL; 

    get_absolutePath(TEST_URLS_FILE, &urlsFileSrc);

    if(urlsFileSrc != NULL)
        fileToFifo(urlsFileSrc, urls_fifo);

    if(urls_fifo !=  NULL) {
        url = pop(urls_fifo);
        get_absolutePath(TEST_DOWNLOAD_FILE, &downloadPageSrc);

        if(downloadPageSrc != NULL && url != NULL) {
            //downloadPage(url->value, downloadPageSrc);
            downloadPage_bycontains(url->value, downloadPageSrc, YINITDATA_VAR);
            extract_htmlpagedata(downloadPageSrc);
            freeElement(url);
            free(downloadPageSrc);
        }
        
        free(urlsFileSrc);
        freeFile(urls_fifo);
    } 
    return 0;
}