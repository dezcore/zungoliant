#include "./../include/testy.h" 

int extract_htmlpagedata_(char *downloadPage, char *saveFilePath) {
    char *contents;
    char rpl[] = " ";
    char *parseContentPath = NULL; 
    char *patterns[] = {TEST_VAR_REGEX, ";$"};

    if(downloadPage != NULL) {
        parseYFile(downloadPage);
        contents = (char*) malloc(sizeof(char));        
        get_absolutePath(TEST_YINITDATA_FILE_PATH, &parseContentPath);

        if(parseContentPath != NULL && saveFilePath != NULL) {
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {
                for(int i = 0; i < 2; i++) {
                    regex_replace(&contents, patterns[i], rpl);
                }
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

int test_downloadPage_and_replace_(char *url, char *parseContent ) {
    char *downloadPageSrc = NULL; 
    get_absolutePath(TEST_DOWNLOAD_FILE, &downloadPageSrc);

    if(downloadPageSrc != NULL) {
        downloadPage_bycontains(url, downloadPageSrc, YINITDATA_VAR);
        extract_htmlpagedata_(downloadPageSrc, parseContent);
        free(downloadPageSrc);
    }

    return 0;
}

int test_get_root_field(char *url, struct json_object **json) {
    char* parseFile = NULL;
    get_absolutePath(TEST_PARSE_FILE_PATH, &parseFile);

    if(parseFile != NULL) {
        test_downloadPage_and_replace_(url, parseFile);
        file_tojson(parseFile, &(*json));
        free(parseFile);
    }

    return 0;
}

int test_video_page_items() {
    unsigned int ii;
    struct json_object *json, *results = NULL;
    struct json_object *video, *titleObj, *videoIdObj/*, *imgObj*/;

    test_get_root_field(TEST_YOUTUBE_VIDEOPAGE_URL, &json);

    if(json != NULL) {
        results = getObj_rec(json, VIDEO_PAGE_ROOT_FIELD);
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
        json_object_put(json);
    }
    return 0;
}

int test_video_page_channel() {
    struct json_object *json, *rootObj = NULL;
    struct json_object *titleObj, *descriptionObj, *viewCountObj, *channelTitleObj, *channelImgObj, *channelUrlObj;
    test_get_root_field(TEST_YOUTUBE_VIDEOPAGE_URL, &json);

    if(json != NULL) {
        rootObj = getObj_rec(json, VIDEO_PAGE_CHANNEL_ROOT_FIELD);
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

        json_object_put(json);
    }

    return 0;
}

int test_channel_page_home() {
    //#define CHANNEL_PAGE_HOME_TAB_CONTENT_FIELD "/0/tabRenderer/content/sectionListRenderer/contents"
    struct json_object *json, *rootObj = NULL;
    struct json_object *channelHomeTabUrlObj/*,  *descriptionObj ,*viewCountObj, *channelTitleObj, *channelImgObj, *channelUrlObj*/;

    test_get_root_field(TEST_YOUTUBE_CHANNELPAGE_URL, &json);
    
    printf("channel_page_home (1) : %d\n", (json != NULL));
    if(json != NULL) {
        rootObj = getObj_rec(json, CHANNEL_PAGE_ROOT_FIELD);
        printf("channel_page_home (2) : %d\n", (json != NULL));
        channelHomeTabUrlObj = getObj_rec(rootObj, CHANNEL_PAGE_HOME_TAB_FIELD);

        if(channelHomeTabUrlObj != NULL) {
            printf("Url : %s\n", json_object_get_string(channelHomeTabUrlObj));
        }

        json_object_put(json);
    }

    return 0;
}