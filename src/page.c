#include "./../include/page.h"

int print_patterns(char **patterns, size_t len) {
    if(patterns != NULL) {
        for(int i = 0; i < len; i++) {
            if(patterns[i] != NULL) {
                printf("Pattern : %s\n", patterns[i]);
            }
        }
    }
    return 0;
}

int print_page(YPage *page) {
    if(page != NULL) {
        printf("Url : %s, regex : %s\n", page->url, page->regex);
        print_patterns(page->patterns, page->patterns_len);
    }
    return 0;
}

char** init_patterns(char **defaultPatterns, size_t len) {
    char **patterns = malloc(len * sizeof(char*));

    if(defaultPatterns != NULL) {
        for(int i = 0; i < len; i++) {
            patterns[i] = (char*) calloc(DEFAULT_STR_LEN, sizeof(char));
            if(patterns[i] != NULL) {
                sprintf(patterns[i], "%s", defaultPatterns[i]);
            }
        }
    }

    return patterns;
}

int init_yPage(YPage *page, int type, char *url, char *replace) {
    char **patterns = type == 0 ? DEFAULT_PATTERNS : CONTENTS_PATTERNS;
    size_t patterns_len = 0 ? DEFAULT_PATTERNS_LEN : CONTENTS_PATTERNS_LEN;
    page->patterns_len = patterns_len;
    page->patterns = init_patterns(patterns, patterns_len); 
    page->url = (char*) calloc(DEFAULT_STR_LEN, sizeof(char));
    page->replace = (char*) calloc(DEFAULT_STR_LEN, sizeof(char));
    page->regex = type == 0 ? NULL : (char*) calloc((strlen(CONTENT_REGEX)+1), sizeof(char));

    if(url != NULL && page->replace != NULL) {
        sprintf(page->url, "%s", url);
        sprintf(page->replace, "%s", replace);
    }

    if(page->regex != NULL)
        sprintf(page->regex, "%s", CONTENT_REGEX);
    
    return 0;
}

int set_url(YPage *page, char *url) {

    if(page != NULL && url != NULL) {
        //page->url = (char*) realloc(page->url, (strlen(url)) * sizeof(char));
        //strcpy(page->url, url);
         sprintf(page->url, "%s", url);
    }
    
    return 0;
}

int free_patterns(char **patterns, size_t len) {
    if(patterns != NULL) {
        for(int i = 0; i < len; i++) {
            free(patterns[i]);
        }
        free(patterns);
    }
    return 0;
}

int free_yPage(YPage *page) {
    free(page->url);
    free(page->replace);
    free_patterns(page->patterns, page->patterns_len);
    if(page->regex != NULL)
        free(page->regex);
    json_object_put(page->json);
    free(page);
    return 0;
}