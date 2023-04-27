#ifndef YBOT_H_
#define YBOT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/json.h"
#include "./../include/zregex.h"
#include "./../include/fifo.h"
#include "./../include/file.h"
#include "./../include/curl.h"
#include "./../include/parser.h"

#define URLS_FILE "/data/file/urls"
#define DOWNLOAD_FILE "/data/file/download"
#define YINITDATA_FILE_PATH "/data/file/ytInitialData"
#define YRESULTS_FIELDS  "/contents/twoColumnWatchNextResults/secondaryResults/secondaryResults/results"

typedef struct _Ybot {
    File *urls_fifo;
    Yfile *data_fifo;
} Ybot;

int run_ybot();
#endif