#ifndef TESTY_H_
#define TESTY_H_
#include "./../include/utility.h"
#include "./youtube/page.h"

#define TEST_PARSE_FILE_PATH "/data/test/parse/ytInitialData.json"
#define TEST_YINITDATA_FILE_PATH "/data/file/ytInitialData"
#define TEST_DEFAULT_REGEX_FILE_PATH "/data/test/ytInitialData_regex"
#define TEST_REPLACE_REGEX_FILE_PATH "/data/test/regex/test.json"

#define TEST_YOUTUBE_HOMEPAGE_URL "https://www.youtube.com"
#define TEST_YOUTUBE_CHANNELPAGE_URL "https://www.youtube.com/@Tribl"
#define TEST_YOUTUBE_VIDEOPAGE_URL "https://www.youtube.com/watch?v=Onjxmdryox0&ab_channel=TRIBL"
#define TEST_YOUTUBE_VIDEOSPAGE_URL ""
int test_video_page_items();
int test_video_page_channel();
int test_channel_page_home();
#endif