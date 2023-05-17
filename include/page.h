#ifndef PAGE_H_
#define PAGE_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <json.h>
#define DEFAULT_STR_LEN 100

//Regex
//https://en.wikibooks.org/wiki/Regular_Expressions/POSIX_Basic_Regular_Expressions

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

int init_yPage(YPage *page, int type, char *url, char *replace);
int set_url(YPage *page, char *url);
int print_page(YPage *page);
int free_yPage(YPage *page);
#endif