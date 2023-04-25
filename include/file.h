#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "./../include/fifo.h"

int existFile(char *fileName);
int createFile(char *fileName);
int printContent(char *filePath);
char* getAbsolutePath(const char *path);
int fileToFifo(char *filePath, File *file);
int getCurrentDir(char *res,  size_t size);
int appendStrToFile(char *fileName, const char* str);
char* load_file(const char* filename,  char *fileContent);
#endif