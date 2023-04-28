#include "./../include/testzregex.h"
#define STR_SIZE 100

int test_regex_replace() {
    char rpl[] = " ";
    char *contents = (char*) malloc(sizeof(char));    
    char *patterns[] = {TEST_VAR_REGEX,  ";$"};
    
    char *fileContent = (char*) malloc(sizeof(char));
    char *filePath = getAbsolutePath(TEST_DEFAULT_REGEX_FILE_PATH);
    char *saveFilePath = getAbsolutePath(TEST_REPLACE_REGEX_FILE_PATH);

    fileContent = load_file(filePath, fileContent);

    for(int i = 0; i < 2; i++) {
        regex_replace(&fileContent, patterns[i], rpl);
        appendStrToFile(saveFilePath, fileContent);
    }

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
    char *patterns[] = {TEST_VAR_REGEX, ";$"};

    if(downloadPage != NULL) {
        parseYFile(downloadPage);
        contents = (char*) malloc(sizeof(char));        

        get_absolutePath(TEST_YINITDATA_FILE_PATH, &parseContentPath);
        get_absolutePath(TEST_PARSE_FILE_PATH, &saveFilePath);

        if(parseContentPath != NULL && saveFilePath != NULL) {
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {
                for(int i = 0; i < 2; i++) {
                    regex_replace(&contents, patterns[i], rpl);
                }
                appendStrToFile(saveFilePath, contents);
                free(contents);
            } else {
                printf("Empty content (extract_htmlpagedata)\n");
            }

            free(saveFilePath);
            free(parseContentPath);
        }
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