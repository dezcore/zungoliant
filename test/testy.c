#include "./../include/testy.h" 

int extract_htmlpagedata_(char *downloadPage, char *saveFilePath, char *regex, char *patterns[], size_t patterns_len, char* rpl) {
    char *contents;
    //char rpl[] = " ";
    char *parseContentPath = NULL; 
    //char *patterns[] = {TEST_VAR_REGEX, ";$"};
    //char *patterns[] = {"\"contents\":", ",\"header\""};

    if(downloadPage != NULL) {
        parseYFile(downloadPage);
        contents = (char*) malloc(sizeof(char));        
        get_absolutePath(TEST_YINITDATA_FILE_PATH, &parseContentPath);

        if(parseContentPath != NULL && saveFilePath != NULL) {
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {

                if(regex != NULL)
                    get_nested_json(&contents, regex);

                if(0 < patterns_len) {
                    replace_all(&contents, patterns, rpl, patterns_len);
                }

                //get_nested_json(&contents, TEST_CONTENT_REGEX);
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

int test_downloadPage_and_replace_(char *url, char *parseContent, char *regex, char *patterns[], size_t patterns_len, char* rpl) {
    char *downloadPageSrc = NULL; 
    get_absolutePath(TEST_DOWNLOAD_FILE, &downloadPageSrc);

    if(downloadPageSrc != NULL) {
        downloadPage_bycontains(url, downloadPageSrc, YINITDATA_VAR);
        extract_htmlpagedata_(downloadPageSrc, parseContent, regex, patterns, patterns_len, rpl);
        free(downloadPageSrc);
    }

    return 0;
}

int test_get_root_field(char *url, struct json_object **json, char *regex, char *patterns[], size_t patterns_len, char* rpl) {
    char* parseFile = NULL;
    get_absolutePath(TEST_PARSE_FILE_PATH, &parseFile);

    if(parseFile != NULL) {
        test_downloadPage_and_replace_(url, parseFile, regex, patterns, patterns_len, rpl);
        file_tojson(parseFile, &(*json));
        free(parseFile);
    }
    
    return 0;
}

int test_video_page_items() {
    unsigned int ii;
    struct json_object *json, *results = NULL;
    struct json_object *video, *titleObj, *videoIdObj/*, *imgObj*/;

    test_get_root_field(TEST_YOUTUBE_VIDEOPAGE_URL, &json, NULL, TEST_DEFAULT_PATTERNS, TEST_DEFAULT_PATTERNS_LEN, " ");

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
    test_get_root_field(TEST_YOUTUBE_VIDEOPAGE_URL, &json, NULL, TEST_DEFAULT_PATTERNS, TEST_DEFAULT_PATTERNS_LEN, " ");

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
    struct json_object *json = NULL, *rootObj = NULL;
    struct json_object *channelHomeTabUrlObj/*,  *descriptionObj ,*viewCountObj, *channelTitleObj, *channelImgObj, *channelUrlObj*/;
    test_get_root_field(TEST_YOUTUBE_CHANNELPAGE_URL, &json, TEST_CONTENT_REGEX, TEST_CONTENTS_PATTERNS, TEST_CONTENTS_PATTERNS_LEN, " ");

    if(json != NULL) {
        rootObj = getObj_rec(json, CHANNEL_PAGE_ROOT_FIELD);
        channelHomeTabUrlObj = getObj_rec(rootObj, CHANNEL_PAGE_HOME_TAB_FIELD);

        if(channelHomeTabUrlObj != NULL) {
            printf("Url : %s\n", json_object_get_string(channelHomeTabUrlObj));
        }

        json_object_put(json);
    }

    return 0;
}
