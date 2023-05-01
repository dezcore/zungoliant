#ifndef UTILITY_H_
#define UTILITY_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include<sys/wait.h>
#include<unistd.h>

#define PWD_STR_LEN 100

int trim(char ** str);
int get_pwd(char **res, char *concatPath);
#endif