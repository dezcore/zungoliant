#ifndef ZREGEX_H_
#define ZREGEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#include "./../include/file.h"

#define STR_SIZE 100
#define EXPRESSION_SIZE 100

typedef struct _PATTERN {
    char *value;
} PATTERN;

typedef struct _PATTERNS {
    PATTERN *patterns;
    int size;
} PATTERNS;

int free_pattern(PATTERN *pattern);
int free_patterns(PATTERNS *array);
int init_pattern(PATTERN **pattern);
int print_pattern(PATTERN *pattern);
int print_patterns(PATTERNS *patterns);
int search(char *filePath, char *expression);
int init_patterns(PATTERNS *array, int size);
int resize_patterns(PATTERNS *array, int size);
int set_patterns(PATTERNS *patterns, int size);
int set_pattern_value(PATTERN *pattern, char *value);
int get_nested_json(char **str, const char *pattern);
int replace_substring(char **str, const char *pattern, char* replace);
int regex_replace(char **str, const char *pattern, const char *replace);
int replace_all(char **contents, PATTERNS *patterns, char rpl[]);
#endif