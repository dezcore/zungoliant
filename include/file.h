#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int getCurrentDir(char *res,  size_t size);
int existFile(char *fileName);
int printContent(char *filePath);
#endif