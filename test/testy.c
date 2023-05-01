#include "./../include/testy.h" 

int extract_htmlpagedata_(char *downloadPage, char *saveFilePath, YPage *page) {
    char *contents;
    char *parseContentPath = NULL; 

    if(downloadPage != NULL) {
        parseYFile(downloadPage);
        contents = (char*) malloc(sizeof(char));        
        get_absolutePath(TEST_YINITDATA_FILE_PATH, &parseContentPath);

        if(parseContentPath != NULL && saveFilePath != NULL) {
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {
                trim(&contents);
                if(page->regex != NULL)
                    get_nested_json(&contents, page->regex);

                if(0 < page->patterns_len)
                    replace_all(&contents, page->patterns, page->replace, page->patterns_len);

                appendStrToFile(saveFilePath, contents);
                free(contents);
            } else {
                printf("Empty content (extract_htmlpagedata)\n");
            }

            free(parseContentPath);
        }
    }

    return 0;
}

int test_downloadPage_and_replace_(char *parseContent, YPage *page) {
    char *downloadPageSrc = NULL; 
    get_pwd(&downloadPageSrc, TEST_DOWNLOAD_FILE);

    if(downloadPageSrc != NULL) {
        downloadPage_bycontains(&page->url, downloadPageSrc, YINITDATA_VAR);
        //extract_htmlpagedata_(downloadPageSrc, parseContent, page);
        free(downloadPageSrc);
    }

    return 0;
}

int test_get_root_field(YPage *page) {
    char* parseFile = NULL;
    get_pwd(&parseFile, TEST_PARSE_FILE_PATH);

    if(parseFile != NULL) {
        test_downloadPage_and_replace_(parseFile, page);
        //file_tojson(parseFile, &(*json));
        free(parseFile);
    }
    
    return 0;
}

int test_video_page_items() {
    unsigned int ii;
    YPage *page = malloc(sizeof(*page));
    struct json_object *results = NULL;
    struct json_object *video, *titleObj, *videoIdObj/*, *imgObj*/;

    init_yPage(page, 0, TEST_YOUTUBE_VIDEOPAGE_URL, " ");
    test_get_root_field(page);

    if(page != NULL) {
        results = getObj_rec(page->json, VIDEO_PAGE_ROOT_FIELD);
        if(results != NULL) {
            for(ii = 0; ii < json_object_array_length(results); ii++){
		        video = json_object_array_get_idx(results, ii);
                titleObj = getObj_rec(video, VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD);
                videoIdObj =  getObj_rec(video, VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD);
                //imgObj = getObj_rec(video, VIDEO_PAGE_PLAYLIST_ITEM_IMG_FIELD);

                if(titleObj != NULL && videoIdObj != NULL /*&& imgObj != NULL*/) {
                    printf("title : %s, videoId : %s\n", 
                        json_object_get_string(titleObj), json_object_get_string(videoIdObj)/*, json_object_get_string(imgObj)*/
                    );
                }
	        }
        }
        free_yPage(page);
    }
    return 0;
}

int test_video_page_channel() {
    YPage *page = malloc(sizeof(*page));
    struct json_object *rootObj = NULL;
    struct json_object *titleObj, *descriptionObj, *viewCountObj, *channelTitleObj, *channelImgObj, *channelUrlObj;

    init_yPage(page, 0, TEST_YOUTUBE_VIDEOPAGE_URL, " ");
    test_get_root_field(page);

    if(page != NULL) {
        rootObj = getObj_rec(page->json, VIDEO_PAGE_CHANNEL_ROOT_FIELD);
        titleObj = getObj_rec(rootObj, VIDEO_PAGE_TITLE_FIELD);
        channelTitleObj = getObj_rec(rootObj, VIDEO_PAGE_CHANNEL_TITLE_FIELD);
        channelImgObj = getObj_rec(rootObj, VIDEO_PAGE_CHANNEL_IMG_FIELD);
        channelUrlObj = getObj_rec(rootObj, VIDEO_PAGE_CHANNEL_URL_FIELD);
        descriptionObj = getObj_rec(rootObj, VIDEO_PAGE_DESCRIPTION_FIELD);
        viewCountObj =  getObj_rec(rootObj, VIDEO_VIEWCOUNT_SHORT_FIELD);

        if(titleObj != NULL && descriptionObj != NULL && viewCountObj != NULL) {
            printf("title : %s, description : %s, viewCount : %s\n %s, %s, %s\n", 
                json_object_get_string(titleObj), json_object_get_string(descriptionObj), json_object_get_string(viewCountObj),
                json_object_get_string(channelTitleObj), json_object_get_string(channelUrlObj), json_object_get_string(channelImgObj)
            );
        }
        free_yPage(page);
    }

    return 0;
}

int test_channel_page_home_videos(struct json_object *videosContentObj) {
    unsigned int i;
    struct json_object *videoObj;
    struct json_object *videoIdObj, *titleObj, /* *descriptionObj,*/ *viewCountObj, /*videoCountObj,*/ *videoUrlObj;

    if(videosContentObj != NULL) {
        printf("\n  test_channel_page_home_videos : \n");
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
                //descriptionObj = getObj_rec(videoObj, CHANNEL_PAGE_HOME_VIDEO_DESCRIPTION_FIELD);
                printf("VideoId : %s\n", json_object_get_string(videoIdObj));
                printf("Title : %s\n", json_object_get_string(titleObj));
                printf("ViewCount : %s\n", json_object_get_string(viewCountObj));
                printf("Url : %s\n", json_object_get_string(videoUrlObj));

            }
        }
    }
    return 0;
}

int test_channel_page_home() {
    unsigned int i;
    YPage *page = malloc(sizeof(*page));
    //struct json_object *homeUrlObj;
    //struct json_object *json = NULL, *rootObj = NULL, *tabsObj = NULL, *tabObj = NULL, *contents = NULL;

    init_yPage(page, 1, TEST_YOUTUBE_CHANNELPAGE_URL, " ");
    test_get_root_field(page);
    free_yPage(page);

    /*if(page != NULL) {
        rootObj = getObj_rec(json, CHANNEL_PAGE_ROOT_FIELD);
        if(rootObj != NULL) {
            tabsObj = getObj_rec(rootObj, CHANNEL_PAGE_TABS_FIELD);

            if(tabsObj != NULL) {
                for(i = 0; i < json_object_array_length(tabsObj); i++) {
                    if(i == 0) {
                        tabObj = json_object_array_get_idx(tabsObj, i);
                        if(tabObj != NULL) {
                            homeUrlObj = getObj_rec(tabObj, CHANNEL_PAGE_HOME_TAB_URL_FIELD);
                            contents =  getObj_rec(tabObj, CHANNEL_PAGE_HOME_TAB_CONTENTS_FIELD);
                            //#define CHANNEL_PAGE_HOME_TAB_CONTENTS_FIELD
                            printf("Url : %s\n", json_object_get_string(homeUrlObj));
                            
                            if(contents)
                                test_channel_page_home_videos(contents);
                        }
                       
                    }
                }
            }
        }
        free_yPage(page);
        json_object_put(json);
    }*/

    return 0;
}
