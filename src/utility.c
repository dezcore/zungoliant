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
        puts("test trim");
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