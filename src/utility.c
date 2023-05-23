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

int get_match(char *str, char *pattern, File *fifo) {
    char *res; 
    regex_t reg;
    size_t nmatch;
    int start, end, curs = 0;
    char *strCpy = (char *) malloc(strlen(str) * sizeof(char));

    if(fifo != NULL && str != NULL && pattern != NULL && !regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];
        sprintf(strCpy, "%s", str);

        while(!regexec(&reg, strCpy, nmatch + 1, m, 0)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            curs += m[0].rm_eo;
            res = (char*) malloc((end - start + 1) * sizeof(char));

            if(res != NULL) {
                strncpy(res, &strCpy[start], end-start);
                res[end-start] = '\0';
                memcpy(strCpy, &str[curs], (strlen(str)-curs));
                strCpy[(strlen(str)-curs)] = '\0';
                push(fifo, res);
                free(res);
            }
        }
        free(strCpy);
    }

    return 0;
}

int get_str_match(char *str, char *pattern, char **match) {
    char *res; 
    regex_t reg;
    size_t nmatch;
    int start, end;

    if(str != NULL && pattern != NULL && !regcomp(&reg, pattern, REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        if(!regexec(&reg, str, nmatch + 1, m, 0)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            res = (char*) malloc((end-start+1) * sizeof(char));

            if(res != NULL) {
                strncpy(res, &str[start], end-start);
                res[end-start] = '\0';
                *match = res;
            }
        }
    }

    return 0;
}

int join_file_element(File *file, char **str, char *delimiter, int start_delimiter) {
    Element *current;

    if(file != NULL) {
        *str = (char*) calloc(JOIN_STR_LEN, sizeof(char));
        current = file->head;

        if(start_delimiter)
            sprintf(*str, "%s", delimiter);

        while(current != NULL) {
            strcat(*str, current->value);
            strcat(*str, delimiter);
            current = current->next;
        }
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

int fifoToArray(File *fifo, ARRAY **array) {
    int cpt = 0;
    Element *current;

    if(fifo != NULL) {
        current = fifo->head;
        init_array(&(*array), fifo->size, 5, "");

        while(current != NULL) {
            (*array)->elements[cpt] = (char*) realloc((*array)->elements[cpt], (strlen(current->value)+1) * sizeof(char));
            if((*array)->elements[cpt] != NULL) {
                sprintf((*array)->elements[cpt], "%s", current->value);
            } 
            cpt++;
            current = current->next;
        }
    }

    return 0;
}

int parseDate(char *str_date, char *datePartRegex, char *datePartDelimiter, ARRAY **array) {
    char *part = NULL;
    File *fifo = malloc(sizeof(*fifo));
    get_str_match(str_date, datePartRegex, &part); 
    fifo_init(fifo);
    if(part != NULL) {
        get_match(part, datePartDelimiter, fifo);
        if(fifo != NULL) {
            //display(fifo);
            fifoToArray(fifo, &(*array));
            freeFile(fifo);
        }
        free(part);
    }

  return 0;
}