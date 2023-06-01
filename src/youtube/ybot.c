#include "../../include/youtube/ybot.h"

int init_ybot(Ybot **bot) {
    *bot = malloc(sizeof(*bot));

    if(*bot != NULL) {
        (*bot)->urls_fifo = init();
        init_yfile(&(*bot)->data_fifo);
    }

    return 0;
}

int free_ybot(Ybot *bot) {
    if(bot != NULL) {
        freeFile(bot->urls_fifo);
        free_yfile(&(bot->data_fifo));
    }
    free(bot);
    return 0;
}

int channel_page_home_videos(struct json_object *videosContentObj) {
    unsigned int i;
    struct json_object *videoObj;
    struct json_object *videoIdObj, *titleObj, /* *descriptionObj,*/ *viewCountObj, /*videoCountObj,*/ *videoUrlObj;

    if(videosContentObj != NULL) {
        printf("\n  channel_page_home_videos : \n");
        for(i = 0; i < json_object_array_length(videosContentObj); i++) {
            videoObj = json_object_array_get_idx(videosContentObj, i);
            if(videoObj != NULL) {
                
                if(i == 0) {
                    videoIdObj = getObj_rec(videoObj, CHANNEL_PAGE_HOME_VIDEOID_FIELD);
                    titleObj =  getObj_rec(videoObj, CHANNEL_PAGE_HOME_VIDEO_TITLE_FIELD);
                    viewCountObj =  getObj_rec(videoObj, CHANNEL_PAGE_HOME_VIDEO_VIEWCOUNT_FIELD);
                    videoUrlObj = getObj_rec(videoObj, CHANNEL_PAGE_HOME_VIDEO_URL_FIELD);
                } else if(i == 1) {
                    videoIdObj = getObj_rec(videoObj, CHANNEL_PAGE_HOME_ITEM_VIDEOID_FIELD);
                    titleObj =  getObj_rec(videoObj, CHANNEL_PAGE_HOME_ITEM_VIDEO_TITLE_FIELD);
                    viewCountObj =  getObj_rec(videoObj, CHANNEL_PAGE_HOME_ITEM_VIDEO_VIEWCOUNT_FIELD);
                    videoUrlObj = getObj_rec(videoObj, CHANNEL_PAGE_HOME_ITEM_VIDEO_URL_FIELD);
                }

                if(i == 0 || i == 1) {
                    //descriptionObj = getObj_rec(videoObj, CHANNEL_PAGE_HOME_VIDEO_DESCRIPTION_FIELD);
                    printf("VideoId : %s\n", json_object_get_string(videoIdObj));
                    printf("Title : %s\n", json_object_get_string(titleObj));
                    printf("ViewCount : %s\n", json_object_get_string(viewCountObj));
                    printf("Url : %s\n", json_object_get_string(videoUrlObj));
                }

            }
        }
    }
    return 0;
}

int channel_videos_tabs_videos(struct json_object *videosContentObj) {
    unsigned int i;
    struct json_object *videoObj;
    struct json_object *videoIdObj, *titleObj, /* *descriptionObj,*/ *viewCountObj, /*videoCountObj,*/ *videoUrlObj;

    printf("\n  channel_videos_tabs : \n");
    if(videosContentObj != NULL) {
        for(i = 0; i < json_object_array_length(videosContentObj); i++) {
            videoObj = json_object_array_get_idx(videosContentObj, i);
            if(videoObj != NULL) {
                if(i == 0) {
                    videoIdObj = getObj_rec(videoObj, VIDEOS_PAGE_VIDEOID_FIELD);
                    titleObj =  getObj_rec(videoObj, VIDEOS_PAGE_VIDEO_TITLE_FIELD);
                    viewCountObj =  getObj_rec(videoObj, VIDEOS_PAGE_VIDEO_VIEWCOUNT_FIELD);
                    videoUrlObj = getObj_rec(videoObj, VIDEOS_PAGE_VIDEO_URL_FIELD);
                    //descriptionObj = getObj_rec(videoObj, VIDEOS_PAGE_VIDEO_DESCRIPTION_FIELD);
                    printf("VideoId : %s\n", json_object_get_string(videoIdObj));
                    printf("Title : %s\n", json_object_get_string(titleObj));
                    printf("ViewCount : %s\n", json_object_get_string(viewCountObj));
                    printf("Url : %s\n", json_object_get_string(videoUrlObj));
                }
            }
        }
    }
    return 0;
}

int channels_tabs(struct json_object *videosContentObj) {
    unsigned int i;
    struct json_object *videoObj;
    struct json_object *channelIdObj, *titleObj, *subscriberCountObj, *channelUrlObj;
    //struct json_object *imgObj;

    printf("\n channels_tabs : \n");
    if(videosContentObj != NULL) {
        for(i = 0; i < json_object_array_length(videosContentObj); i++) {
            videoObj = json_object_array_get_idx(videosContentObj, i);
            if(videoObj != NULL) {
                if(i == 0) {
                    //imgObj = getObj_rec(videoObj, CHANNELS_PAGE_ITEM_CHANNELIMG_FIELD);
                    channelIdObj = getObj_rec(videoObj, CHANNELS_PAGE_ITEM_CHANNELID_FIELD);
                    titleObj =  getObj_rec(videoObj, CHANNELS_PAGE_ITEM_CHANNELTITLE_FIELD);
                    subscriberCountObj =  getObj_rec(videoObj, CHANNELS_PAGE_ITEM_CHANNELSUBSCRIBERCOUNT_FIELD);
                    channelUrlObj = getObj_rec(videoObj, CHANNELS_PAGE_ITEM_CHANNELURL_FIELD);

                    //printf("Img src : %s\n", json_object_get_string(imgObj));
                    printf("ChannelId : %s\n", json_object_get_string(channelIdObj));
                    printf("Title : %s\n", json_object_get_string(titleObj));
                    printf("SubscriberCount : %s\n", json_object_get_string(subscriberCountObj));
                    printf("Url : %s\n", json_object_get_string(channelUrlObj));
                }
            }
        }
    }

    return 0;
}

int save_channel_page_home(struct json_object *json, Yfile **data_fifo) {
    unsigned int i;
    struct json_object *homeUrlObj;
    struct json_object *rootObj = NULL, *tabsObj = NULL, *tabObj = NULL, *contents = NULL;

    if(json != NULL && *data_fifo != NULL) {
        rootObj = getObj_rec(json, CHANNEL_PAGE_ROOT_FIELD);
        if(rootObj != NULL) {
            tabsObj = getObj_rec(rootObj, CHANNEL_PAGE_TABS_FIELD);
            if(tabsObj != NULL) {
                for(i = 0; i < json_object_array_length(tabsObj); i++) {
                    tabObj = json_object_array_get_idx(tabsObj, i);
                    if(tabObj != NULL) {
                        homeUrlObj = getObj_rec(tabObj, CHANNEL_PAGE_HOME_TAB_URL_FIELD);
                        printf("Url : %s\n", json_object_get_string(homeUrlObj));

                        if((contents = getObj_rec(tabObj, CHANNELS_PAGE_TAB_CONTENTS_FIELD)) != NULL)
                            channels_tabs(contents);
                        else if((contents = getObj_rec(tabObj, CHANNEL_PAGE_HOME_TAB_CONTENTS_FIELD)) != NULL)
                            channel_page_home_videos(contents);
                        else if((contents = getObj_rec(tabObj, CHANNEL_PAGE_VIDEOS_TAB_CONTENTS_FIELD)) != NULL)
                            channel_videos_tabs_videos(contents);
                    }
                       
                }
            }
        }
    }

    return 0;
}

int channelpage_handler(Ybot **bot, YPage *page1 , struct json_object **json, char *url, char* parseFile) {
    if(url != NULL) {
        printf("channelsPage : %s\n", url);
        //set_url(page1, url);
        //downloadPage_and_replace(parseFile, page1);
        //file_tojson(parseFile, &(*json));
        //save_channel_page_home(*json, &(*bot)->data_fifo);
    }
    return 0;
}

int init_env() {
    char *parseDir = NULL;
    char *regexDir = NULL;
    char *downloadDir = NULL;

    get_pwd(&parseDir, PARSER_DIR_PATH);
    get_pwd(&regexDir, REGEX_DIR_PATH);
    get_pwd(&downloadDir, DOWNLOAD_DIR_PATH);

    if(parseDir != NULL &&  regexDir != NULL && downloadDir != NULL) {
        createDir(parseDir);
        createDir(regexDir);
        createDir(downloadDir);
    }

    free(parseDir);
    free(regexDir);
    free(downloadDir);

    return 0;
}

int init_bot_env(/*Ybot **bot*/) {
    //char *parseFile = NULL, *urlsFileSrc = NULL;
    /*init_env();
    init_ybot(&(*bot));
    init_urls(&bot->urls_fifo, &urlsFileSrc);
    get_pwd(&parseFile, PARSE_FILE_PATH);
    init_bot_pages(&page, &page1);*/
    return 0;
}


int init_bot_pages(YPage **page, YPage **page1) {
    const char* titles_regex = "/data/file/titles_regex";
    init_yPage(page);
    init_yPage(page1);

    if(page != NULL && page1 != NULL) {
        set_yPage(*page, 0,  "", " ", (char*)titles_regex);
        set_yPage(*page1, 1,  "", " ", (char*)titles_regex);
        //print_page(*page);
        //print_page(*page1);
    }    
    return 0;
}

int run_ybot() {
    Ybot *bot = NULL;
    Element *url = NULL; 
    struct json_object *json = NULL;
    YPage *page = NULL, *page1 = NULL;
    char *parseFile = NULL, *urlsFileSrc = NULL;

    init_env();
    init_ybot(&bot);
    init_urls(&bot->urls_fifo, &urlsFileSrc);
    get_pwd(&parseFile, PARSE_FILE_PATH);
    init_bot_pages(&page, &page1);

    if(urlsFileSrc != NULL && page != NULL) {
        while(0 < bot->urls_fifo->size) {
            url = pop(bot->urls_fifo);
            if(url != NULL) {
                if(match_pattern(url->value, ".+watch\\?v.*")) {//VIDEOPAGE
                    videopage_handler(page, url->value, parseFile); 
                } else if(match_pattern(url->value, "@.+")) {// Channel page
                    channelpage_handler(&bot, page1 , &json, url->value, parseFile);
                }
                //print_yfile(bot->data_fifo);
                json_object_put(json);
                freeElement(url);
                //url = NULL;
            }
        }
    }

    free(parseFile);
    free(urlsFileSrc);
    free_yPage(page);
    free_yPage(page1);
    free_ybot(bot);
    return 0;
}