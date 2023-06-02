#ifndef UTILITY_H_
#define UTILITY_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <time.h>
#include <sys/wait.h>
#include<unistd.h>
#include <curl/curl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include "./fifo.h"
#include "./json.h"
#include "./youtube/yfields.h"

#define PWD_STR_LEN 100
#define JOIN_STR_LEN 100

#define YINITDATA_VAR "ytInitialData"
#define DOWNLOAD_TEST_FILE "/data/test/download/test.html"
#define YINITDATA_FILE_PATH "/data/file/ytInitialData"

typedef struct _STR {
    char *value;
} STR;

typedef struct _STR_ARRAY {
    STR *elements;
    size_t length;
} STR_ARRAY;

int trim(char **str);
int init_str_struct(STR *str);
int get_title_season(char *title);
int set_str_value(STR *str, char *value);
int get_pwd(char **res, char *concatPath);
int match_pattern(char *str, char *pattern);
int free_str_array_struct(STR_ARRAY *array);
int free_str_array_struct(STR_ARRAY *array);
int timestamp_to_utc(char *date, char **res);
int print_str(STR *str, char *tabs, char *subtabs);
int get_match(char *str, char *pattern,  File *fifo);
int get_str_match(char *str, char *pattern, char **match);
int init_str_array_struct(STR_ARRAY *array, size_t length);
int resize_str_array_struct(STR_ARRAY *array, size_t length);
int join_file_element(File *file, char **str, char *delimiter, int start_delimiter);
int parseDate(char *str_date, char *datePartRegex, char *datePartDelimiter, STR_ARRAY **array);
int print_array_str(STR_ARRAY *array, char *tabs, char* subtabs, char *str_tabs, char *str_subtabs);
#endif