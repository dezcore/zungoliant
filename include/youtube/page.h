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

typedef struct _YPage {
    char *url;
    char *regex;
    char *replace;
    char **patterns;
    size_t patterns_len;
    struct json_object *json;
} YPage;

int print_page(YPage *page);
int free_yPage(YPage *page);
int set_url(YPage *page, char *url);
int downloadPage_and_replace(char *parseContent, YPage *page);
int init_yPage(YPage *page, int type, char *url, char *replace);
int extract_htmlpagedata(char *html_file_path, char *saveFilePath, YPage *page);
int videopage_handler(YPage *page, STR_ARRAY *titlesRegex, char *url, char* parseFile);

#endif