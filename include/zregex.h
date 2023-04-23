#ifndef ZREGEX_H_
#define ZREGEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#define STR_SIZE 100
#define EXPRESSION_SIZE 100

int search(char *filePath, char *expression);
#endif