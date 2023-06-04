#ifndef PAGE_H_
#define PAGE_H_

#include "../file.h"
#include "../parser.h"
#include "../curl.h"
#include "../zregex.h"
#include "../db/mongodb_bson.h"
#include "../utility.h"

#define DEFAULT_STR_LEN 100

#define DEFAULT_PATTERNS_LEN 2
#define CONTENTS_PATTERNS_LEN 2
#define CONTENT_REGEX "\"contents\".+\"header\""
#define VAR_REGEX "[ \t]*var[ \t]*[A-Za-z]+[ \t]*=[ \t]*"
#define CONTENTS_PATTERNS (char*[]) {"^(\"([a-z])*\":)", ",\"header\"$"}
#define DEFAULT_PATTERNS (char*[]) {"[ \t]*var[ \t]*[A-Za-z]+[ \t]*=[ \t]*", ";$"}

typedef struct _PAGEPATTERN {
    char *url;
    char *regex;
    char *replace;
} PAGEPATTERN;

typedef struct _YPage {
    int type;
    PATTERNS *patterns;
    STR_ARRAY *titlesRegex;
    struct json_object *json;
    PAGEPATTERN *page_pattern;
    mongoc_client_t *mongo_client;
} YPage;

int print_page(YPage *page);
int free_yPage(YPage *page);
int init_yPage(YPage *page);
int init_page_pattern_paramters(PAGEPATTERN *pattern);
int set_page_pattern_url(PAGEPATTERN  *pattern, char *url);
int downloadPage_and_replace(char *parseContent, YPage *page);
int videopage_handler(YPage *page, char *url, char* parseFile);
int set_page_pattern_regex(PAGEPATTERN  *pattern, char *regex);
int set_page_pattern_replace(PAGEPATTERN  *pattern, char *replace);
int extract_htmlpagedata(char *html_file_path, char *saveFilePath, YPage *page);
int set_yPage(YPage *page, int type, char *url, char *replace, char *titlesRegexFilePath);
#endif