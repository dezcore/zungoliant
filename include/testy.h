#ifndef TESTY_H_
#define TESTY_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../include/fifo.h"
#include "./../include/file.h"
#include "./../include/json.h"
#include "./../include/curl.h"
#include "./../include/zregex.h"
#include "./../include/parser.h"
#include "./../include/yfields.h"

#define YINITDATA_VAR "ytInitialData"
#define TEST_DOWNLOAD_FILE "/data/test/download/test.html"
#define TEST_PARSE_FILE_PATH "/data/test/parse/ytInitialData.json"
#define TEST_YINITDATA_FILE_PATH "/data/file/ytInitialData"
#define TEST_DEFAULT_REGEX_FILE_PATH "/data/test/ytInitialData_regex"
#define TEST_REPLACE_REGEX_FILE_PATH "/data/test/regex/test.json"

#define TEST_YOUTUBE_HOMEPAGE_URL "https://www.youtube.com"
#define TEST_YOUTUBE_CHANNELPAGE_URL "https://www.youtube.com/@Tribl"
#define TEST_YOUTUBE_VIDEOPAGE_URL "https://www.youtube.com/watch?v=Onjxmdryox0&ab_channel=TRIBL"
#define TEST_YOUTUBE_VIDEOSPAGE_URL ""

//Regex
//https://en.wikibooks.org/wiki/Regular_Expressions/POSIX_Basic_Regular_Expressions
#define TEST_VAR_REGEX "[ \t]*var[ \t]*[A-Za-z]+[ \t]*=[ \t]*"

int test_video_page_items();
int test_video_page_channel();
int test_channel_page_home();

#endif