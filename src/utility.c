#include "./../include/utility.h"

int get_matchIndex(char **str, char *pattern, int *start, int *end, int target) {
    regex_t reg;
    size_t nmatch;

    if(!regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        if(!regexec(&reg, *str, nmatch + 1, m, 0)) {
            if(target == 0 || target == 3)
                *start = m[0].rm_so;
            
            if(target == 1 || target == 3)
                *end = m[0].rm_eo;
        }
    }

    return 0;
}

int trim(char ** str) {
    char *res;
    int start = -1, end = -1;
    get_matchIndex(&(*str), "^[ \t]+", &end, &start, 1);
    get_matchIndex(&(*str), "[ \t]+$", &end, &start, 0);
    res = (char*) calloc((strlen(*str)), sizeof(char));

    if(start != end && start != -1 && res != NULL) {
        memcpy(res, &(*str)[start], (end-start));
        sprintf(*str, "%s", res);
        free(res);
    }

    return 0;
}

int get_pwd(char **res, char *concatPath) {
    *res = (char*) malloc(PWD_STR_LEN * sizeof(char));

    if(*res != NULL) {
        if(getcwd(*res, PWD_STR_LEN) == NULL) {
            perror("getcwd() error");
        }
        sprintf(*res, "%s%s", *res, concatPath); 
    }
    
    return 0;
}

int extract_htmlpagedata(char *html_file_path, char *output_file_path, YPage *page) {
    char *contents;
    char *parseContentPath = NULL; 

    if(html_file_path != NULL) {
        parseYFile(html_file_path);
        contents = (char*) malloc(sizeof(char));        
        get_absolutePath(YINITDATA_FILE_PATH, &parseContentPath);

        if(parseContentPath != NULL && output_file_path != NULL) {
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {
                trim(&contents);
                if(page->regex != NULL)
                    get_nested_json(&contents, page->regex);

                if(0 < page->patterns_len)
                    replace_all(&contents, page->patterns, page->replace, page->patterns_len);

                appendStrToFile(output_file_path, contents);
                free(contents);
            } else {
                printf("Empty content (extract_htmlpagedata)\n");
            }

            free(parseContentPath);
        }
    }

    return 0;
}

int downloadPage_and_replace(char *parseContent, YPage *page) {
    char *downloadPageSrc = NULL; 
    get_pwd(&downloadPageSrc, DOWNLOAD_TEST_FILE);

    if(downloadPageSrc != NULL) {
        downloadPage_bycontains(&(page->url), downloadPageSrc, YINITDATA_VAR);
        extract_htmlpagedata(downloadPageSrc, parseContent, page);
        free(downloadPageSrc);
    }

    return 0;
}

int match_pattern(char *str, char *pattern) {
    int match = 0;
    regex_t reg;
    size_t nmatch;

    if(str != NULL && pattern != NULL && !regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        if(!regexec(&reg, str, nmatch + 1, m, 0)) {
            match = 1;
        }
    }

    return match;
}

int get_match(char *str, char *pattern) {
    char *res; 
    regex_t reg;
    size_t nmatch;
    int start, end = 0;

    if(str != NULL && pattern != NULL && !regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        while(!regexec(&reg, str, nmatch + 1, m, end)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            res = (char*) malloc( 100 * sizeof(char));
            if(res != NULL) {
                strncpy(res, &str[start], end-start);
                //res[end-start] = '\0';
                printf("Test match : %s\n", res);
                free(res);
            }
        }

        /*if(!regexec(&reg, str, nmatch + 1, m, 0)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            res = (char*) malloc( 100 * sizeof(char));

            if(res != NULL) {
                strncpy(res, &str[start], end-start);
                //res[end-start] = '\0';
                printf("Test match : %s, %d\n", res,  m[1].rm_so);
                free(res);
            }
        }*/
    }

    return 0;
}

int init_fifo(File **fifo, char *filePath) {
    char *file =  NULL;
    get_pwd(&file, filePath);

    if(file != NULL) {
        fileToFifo(file, *fifo);
        free(file);
    }
    
    return 0;
}

int init_file_to_array(char *filePath, ARRAY **array) {
    char *file =  NULL;
    get_pwd(&file, filePath);

    if(file != NULL) {
        fileToArray(file, &(*array));
        free(file);
    }

    return 0;
}

int init_urls(File **urls_fifo,  char **urlsFileSrc) {
    char *urlsFile =  NULL;

    get_pwd(&urlsFile, URLS_FILE);

    if(urlsFile != NULL) {
        fileToFifo(urlsFile, *urls_fifo);
        *urlsFileSrc = urlsFile;
    }

    return 0;
}