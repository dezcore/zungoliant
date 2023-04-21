#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <myhtml/api.h>

typedef struct res_html {
    char  *html;
    size_t size;
} res_html;

int parseFile(char *filePath);
#endif