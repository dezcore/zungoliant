#ifndef CURL_H_
#define CURL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <curl/curl.h>

int downloadPage(char *url, char *output);

#endif