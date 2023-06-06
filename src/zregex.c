#include "./../include/zregex.h"

int init_pattern(PATTERN *pattern) {      
    if(pattern != NULL)
        pattern->value = (char*) malloc(sizeof(*pattern->value));
    return 0;
}

int set_pattern_value(PATTERN *pattern, char *value) {
    char *new_value;

    if(pattern != NULL && value != NULL) {
        new_value = (char*) realloc(pattern->value, (strlen(value)+1) * sizeof(char));
        if(new_value != NULL) {
            sprintf(new_value, "%s", value);
            pattern->value = new_value;
        }
    }

    return 0;
}

int print_pattern(PATTERN *pattern) {
    if(pattern != NULL) {
        printf("Pattern : {\n");
        printf("\t value : %s\n", pattern->value);
        printf("}\n");
    }

    return 0;
}

int free_pattern(PATTERN *pattern) {
    if(pattern != NULL) {
        free(pattern->value);
        free(pattern);
    }

    return 0;
}

int init_patterns(PATTERNS *array, int size) {
    PATTERN *pattern;

    if(array != NULL) {
        array->patterns = malloc(size * sizeof(*array->patterns));
        for(int i = 0; i < size; i++) {
            pattern = &(array->patterns[i]);
            init_pattern(pattern);
        }
        array->size = size;
    }

    return 0;
}

int free_patterns(PATTERNS *array) {
    PATTERN *pattern;
    if(array != NULL) {
        for(int i = 0; i < array->size; i++) {
            pattern = &(array->patterns[i]);
            free(pattern->value);
        } 
        free(array->patterns);   
    }
    free(array);
    return 0;
}

int set_patterns(PATTERNS *array, int size) {
    PATTERN *pattern;     

    if(array != NULL) {
        for(int i = 0; i < array->size; i++) {
            pattern = &(array->patterns[i]);
            init_pattern(pattern);
        }
        array->size = size;
    }
    return 0;
}

int print_patterns(PATTERNS *array) {
    if(array != NULL) {
        for(int i = 0; i < array->size; i++) {
            print_pattern(& (array->patterns[i]) );
        }
    }
    return 0;
}

int resize_patterns(PATTERNS *array, int size) {
    int start = 0;
    PATTERN *new_array, *pattern;

    if(array != NULL) {
        new_array = (PATTERN *) realloc(array->patterns, size * sizeof(array->patterns));
        if(new_array != NULL) {
            start = array->size;
            for(int i = start; i < size; i++) {
                pattern = &(new_array[i]);
                pattern = (PATTERN*) malloc(sizeof(*pattern));
                init_pattern(pattern);
            }
            array->patterns = new_array;
        }
    }
    return 0;
}

//char *expression = malloc(EXPRESSION_SIZE * sizeof(char));// "^(-)?([0-9]+)((,|.)([0-9]+))?\n$"
int search(char *filePath, char *expression) {
    int reti;
    regex_t regex;
    char msgbuf[100];
    char* fileContent = (char*) malloc(sizeof(char));
    reti = regcomp(&regex, expression, 0);

    if(reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    fileContent = load_file(filePath, fileContent);
    reti = regexec(&regex, fileContent, 0, NULL, 0);

    if(!reti) {
        printf("Match : %s\n", fileContent);
    } else if (reti == REG_NOMATCH) {
        printf("No match\n");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
    free(fileContent); 
    return 0;
}

int get_nested_json(char **str, const char *pattern) {
    char *new; 
    regex_t reg;
    int start, end;
    size_t size, nmatch;

    if(!regcomp(&reg, pattern,  REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];

        if(!regexec(&reg, *str, nmatch + 1, m, 0)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            size = end - start;
            new = (char*) malloc(sizeof(*new) * (size + 1));

            if(new) {
                strncpy(new, &(*str)[start], size);
                new[size] = '\0';
                *str = (char *)realloc(*str, strlen(new) + 1);
                sprintf(*str, "%s", new);
                free(new);
            }
        }

        regfree(&reg);
    } else {
        printf("Could not compile regex: %s\n", pattern);
    }  
    return 0;
}

int cut_pattern(char **str, int start, int end, char* replace) {
    char *res;
    int len = strlen(*str);
    int endSize = 0;
    char *startSubBuff = NULL, *endSubBuff = NULL;

    if(*str != NULL) {
        len = strlen(*str);
        startSubBuff = (char*) calloc((start + 1), sizeof(char));
        endSubBuff = (char*) calloc((len + 1), sizeof(char));
        if(startSubBuff != NULL && endSubBuff != NULL) {
            endSize = len-end;

            strncpy(startSubBuff,  &(*str)[0], start);
            endSubBuff[start] = '\0';

            //memcpy(startSubBuff, &(*str)[0], start);    
            //startSubBuff[start] = '\0';
            
            strncpy(endSubBuff, &(*str)[end], endSize);
            endSubBuff[endSize] = '\0';

            //memcpy(endSubBuff, &(*str)[end], len);
            //endSubBuff[len] = '\0';
            res = (char*) calloc((strlen(startSubBuff) + strlen(replace) + strlen(endSubBuff) + 1), sizeof(char));

            if(res != NULL) {
                strcat(res, startSubBuff);
                strcat(res, replace);
                strcat(res, endSubBuff);
                res[strlen(res)] = '\0';
                //printf("tmp : %s\n", res);
                sprintf(*str, "%s", res);
                free(res);
            }

            free(startSubBuff);
            free(endSubBuff);
        }
    }

    return 0;
}

int replace_substring(char **str, const char *pattern, char* replace) {
    regex_t reg;
    size_t nmatch;
    int start, end;

    if(!regcomp(&reg, pattern,  REG_EXTENDED)) {
        nmatch = reg.re_nsub;
        regmatch_t m[nmatch + 1];
        
        if(!regexec(&reg, *str, nmatch + 1, m, 0)) {
            start = m[0].rm_so;
            end = m[0].rm_eo;
            cut_pattern(&(*str), start, end, replace);
        }

        regfree(&reg);
    }

    return 0;
}

int replace_all(char **contents, PATTERNS *array, char rpl[]) {
    if(*contents != NULL && array != NULL) {
        for(int i = 0; i < array->size; i++) {
            replace_substring(&(*contents), (array->patterns[i]).value, rpl);
        }
    }
    return 0;
}

int regex_replace(char **str, const char *pattern, const char *replace) {
    regex_t reg;

    //if regex can't commpile pattern, do nothing
    if(!regcomp(&reg, pattern, REG_EXTENDED)) {
        size_t nmatch = reg.re_nsub; 
        regmatch_t m[nmatch + 1];
        const char *rpl, *p;
        // count back references in replace
        int br = 0;
        p = replace;
        while(1) { 
            while(*++p > 31); 
            if(*p) br++; 
            else break;
        } // if br is not equal to nmatch, leave
        if(br != nmatch) return 0;
        // look for matches and replace
        char *new;
        while(!regexec(&reg, *str, nmatch + 1, m, 0)) {
            // make enough room
            new = (char *)malloc(strlen(*str) + strlen(rpl));
            if(!new) exit(EXIT_FAILURE);
            *new = 0;
            p = rpl = replace;
            int c;
            strncat(new, *str, m[0].rm_so); // test before pattern
            for(int k=0; k<nmatch; k++) {
                while(*++p > 16); // skip printable char
                c = *p;  // back referenc (e.g. \1, \2, ...)
                strncat(new, rpl, p - rpl); // add head of rpl
                // concat match
                strncat(new, *str + m[c].rm_so, m[c].rm_eo - m[c].rm_so);
                rpl = p++; // skip back reference, next match
            }
            strcat(new, p ); // trailing of rpl
            strcat(new, *str + m[0].rm_eo); // trainling text in *str
            free(*str);
            *str = strdup(new);
            free(new);
        }
        // ajust size
        *str = (char *)realloc(*str, strlen(*str) + 1);
    } else {
        printf("Could not compile regex: %s, %s\n", replace, pattern);
    }
    regfree(&reg);
    return 0;
}