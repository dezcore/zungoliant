#ifndef YBOT_H_
#define YBOT_H_

#include "../utility.h"
#include "./page.h"

#define REGEX_DIR_PATH "/data/file/regex/"
#define PARSER_DIR_PATH "/data/file/parser/"
#define DOWNLOAD_DIR_PATH "/data/file/download/"
#define PARSE_FILE_PATH "/data/test/parse/ytInitialData.json"

typedef struct _Ybot {
    File *urls_fifo;
    Yfile *data_fifo;
} Ybot;

int run_ybot();
int test_oversize_json();
#endif