#ifndef UTILITY_H_
#define UTILITY_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/wait.h>
#include<unistd.h>
#include <curl/curl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>

#include "./../include/fifo.h"
#include "./../include/json.h"
#include "./../include/parser.h"
#include "./../include/yfields.h"
#include "./../include/file.h"
#include "./../include/curl.h"
#include "./../include/zregex.h"
#include "./../include/page.h"
#define PWD_STR_LEN 100

#define YINITDATA_VAR "ytInitialData"
#define DOWNLOAD_TEST_FILE "/data/test/download/test.html"
#define YINITDATA_FILE_PATH "/data/file/ytInitialData"

int trim(char **str);
int get_pwd(char **res, char *concatPath);
int downloadPage_and_replace(char *parseContent, YPage *page);
int extract_htmlpagedata(char *html_file_path, char *saveFilePath, YPage *page);

#endif