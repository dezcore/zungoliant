#ifndef FILE_H_
#define FILE_H_

#include "./../include/utility.h"

int createDir(char *dir_path);
int existFile(char *fileName);
int createFile(char *fileName);
int printContent(char *filePath);
char* getAbsolutePath(const char *path);
int fileToFifo(char *filePath, File *file);
int getCurrentDir(char *res,  size_t size);
int appendStrToFile(char *fileName, const char* str);
int get_absolutePath(const char *path, char **filePath);
char* load_file(const char* filename,  char *fileContent);
#endif