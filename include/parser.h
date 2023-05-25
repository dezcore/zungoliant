#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <myhtml/api.h>
#include "./file.h"
#define STR_SIZE 100
#define FILES_PATH "/data/file/"
#define YINITDATA_FILE "ytInitialData" 
#define YINITPLAYERDATA_FILE "ytInitialPlayerResponse"

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
int parseYFile(char *filePath);
#endif