#ifndef FILE_H_
#define FILE_H_

#include "./utility.h"

int createDir(char *dir_path);
int existFile(char *fileName);
int createFile(char *fileName);
int printContent(char *filePath);
char* getAbsolutePath(const char *path);
int fileToFifo(char *filePath, File *file);
int getCurrentDir(char *res,  size_t size);
int init_fifo(File **fifo, char *filePath);
int fileToArray(char *filePath, STR_ARRAY *array);
int getfileContents(char **output, char* filename);
int appendStrToFile(char *fileName, const char* str);
int init_urls(File **urls_fifo,  char **urlsFileSrc);
int get_absolutePath(const char *path, char **filePath);
int init_file_to_array(char *filePath, STR_ARRAY *array);
int load_file(const char* filename,  char **fileContent);
#endif