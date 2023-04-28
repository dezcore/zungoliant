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

// "/contents/twoColumnWatchNextResults/results/results/contents"
// "/contents/twoColumnWatchNextResults/results/results/contents/0/videoPrimaryInfoRenderer/" :
//-> /dateText/simpleText

//Current Video
#define VIDEO_TITLE_FIELD "/contents/twoColumnWatchNextResults/results/results/contents/0/videoPrimaryInfoRenderer/title/runs/0/text"
#define VIDEO_DESCRIPTION_FIELD "/contents/twoColumnWatchNextResults/results/results/contents/1/videoSecondaryInfoRenderer/attributedDescription/content"
#define VIEWCOUNT_FIELD "/contents/twoColumnWatchNextResults/results/results/contents/0/videoPrimaryInfoRenderer/viewCount/videoViewCountRenderer/viewCount/simpleText"
#define VIEWCOUNT_SHORT_FIELD "/contents/twoColumnWatchNextResults/results/results/contents/0/videoPrimaryInfoRenderer/viewCount/videoViewCountRenderer/shortViewCount/simpleText"

//Channel 
#define CHANNEL_TITLE_FIELD "/contents/twoColumnWatchNextResults/results/results/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/title/runs/0/text"
#define CHANNEL_IMG_FIELD "/contents/twoColumnWatchNextResults/results/results/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/thumbnail/thumbnails/0/url"
#define CHANNEL_URL_FIELD "/contents/twoColumnWatchNextResults/results/results/contents/1/videoSecondaryInfoRenderer/owner/videoOwnerRenderer/title/runs/0/navigationEndpoint/commandMetadata/webCommandMetadata/url"

//PlayList (VIDEO)
#define VIDEOID_FIELD "/compactVideoRenderer/videoId"
#define TITLE_FIELD "/compactVideoRenderer/title/simpleText"
#define LENGTH_FIELD "/compactVideoRenderer/lengthText/simpleText"
#define IMG_FIELD "/compactVideoRenderer/thumbnail/thumbnails/0/url"
#define VIEW_COUNT_FIELD "/compactVideoRenderer/viewCountText/simpleText"
#define URL_FIELD "/compactVideoRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url"

//Youtube Page
#define YOUTBE_VIDEOS_FIELD "/contents/twoColumnBrowseResultsRenderer/tabs/0/tabRenderer/content/richGridRenderer/contents"
//-> /0/richItemRenderer/content/videoRenderer/videoId
//-> /0/richItemRenderer/content/videoRenderer/thumbnail/thumbnails/0/url
//-> /0/richItemRenderer/content/videoRenderer/title/runs/0/text
//-> /0/richItemRenderer/content/videoRenderer/descriptionSnippet/runs/0/text
//-> /0/richItemRenderer/content/videoRenderer/navigationEndpoint/commandMetadata/webCommandMetadata/url





typedef struct _Ybot {
    File *urls_fifo;
    Yfile *data_fifo;
} Ybot;

int run_ybot();
#endif