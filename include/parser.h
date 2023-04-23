#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <myhtml/api.h>
#include "./../include/file.h"
#define STR_SIZE 100

#ifdef _WIN32
    #define MyCORE_FMT_Z "%Iu"
#else
    #define MyCORE_FMT_Z "%zu"
#endif

typedef struct res_html {
    char  *html;
    size_t size;
} res_html;

int parseFile(char *filePath);
#endif