#ifndef TESTZREGEX_H_
#define TESTZREGEX_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../include/fifo.h"
#include "./../include/file.h"
#include "./../include/json.h"
#include "./../include/curl.h"
#include "./../include/zregex.h"
#include "./../include/parser.h"

#define YINITDATA_VAR "ytInitialData"
#define TEST_URLS_FILE "/data/test/urls"
#define TEST_DOWNLOAD_FILE "/data/test/download/test.html"
#define TEST_PARSE_FILE_PATH "/data/test/parse/ytInitialData.json"
#define TEST_YINITDATA_FILE_PATH "/data/file/ytInitialData"
#define TEST_DEFAULT_REGEX_FILE_PATH "/data/test/ytInitialData_regex"
#define TEST_REPLACE_REGEX_FILE_PATH "/data/test/regex/test.json"

int test_regex_replace();
int test_downloadPage_and_replace();
#endif