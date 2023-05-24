#ifndef UTILITY_H_
#define UTILITY_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/wait.h>
#include<unistd.h>
#include <curl/curl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>

#include "./../include/fifo.h"
#include "./../include/json.h"
#include "./../include/parser.h"
#include "./../include/yfields.h"
#include "./../include/file.h"
#include "./../include/curl.h"
#include "./../include/zregex.h"
#include "./../include/page.h"
#include "./../include/array.h"
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
int set_str_value(STR *str, char *value);
int get_pwd(char **res, char *concatPath);
int init_fifo(File **fifo, char *filePath);
int match_pattern(char *str, char *pattern);
int free_str_array_struct(STR_ARRAY *array);
int free_str_array_struct(STR_ARRAY *array);
int print_str(STR *str, char *tabs, char *subtabs);
int init_urls(File **urls_fifo,  char **urlsFileSrc);
int get_match(char *str, char *pattern,  File *fifo);
int init_file_to_array(char *filePath, ARRAY **array);
int get_str_match(char *str, char *pattern, char **match);
int init_str_array_struct(STR_ARRAY *array, size_t length);
int downloadPage_and_replace(char *parseContent, YPage *page);
int extract_htmlpagedata(char *html_file_path, char *saveFilePath, YPage *page);
int join_file_element(File *file, char **str, char *delimiter, int start_delimiter);
int parseDate(char *str_date, char *datePartRegex, char *datePartDelimiter, STR_ARRAY **array);
int print_array_str(STR_ARRAY *array, char *tabs, char* subtabs, char *str_tabs, char *str_subtabs);
#endif