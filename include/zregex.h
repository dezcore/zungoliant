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

int search(char *filePath, char *expression);
int regex_replace(char **str, const char *pattern, const char *replace);
int regex_replace_all(char **str, char **patterns, size_t patterns_size, const char *replace);
#endif