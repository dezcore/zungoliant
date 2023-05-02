#ifndef CURL_H_
#define CURL_H_

#include "./../include/utility.h"

#define COMMAND_SIZE 100

int downloadPage(char **url, char *output);
int downloadPage_bycontains(char **url, char *output, char* contains);

#endif