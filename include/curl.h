#ifndef CURL_H_
#define CURL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <curl/curl.h>
#include "./../include/file.h"

#define COMMAND_SIZE 100

int downloadPage(char *url, char *output);
int downloadPage_bycontains(char *url, char *output, char* contains);

#endif