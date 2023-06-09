#include "./../../include/youtube/page.h"

int extract_htmlpagedata(char *html_file_path, char *output_file_path, YPage *page) {
    char *parseContentPath = NULL;
    char *contents = (char*) calloc(2, sizeof(char));

    if(page != NULL && html_file_path != NULL && contents != NULL) {
        parseYFile(html_file_path);
        get_absolutePath(YINITDATA_FILE_PATH, &parseContentPath);

        if(parseContentPath != NULL && output_file_path != NULL) {
            load_file(parseContentPath, &contents);
            if(contents != NULL) {
                trim(&contents);
                if(strcmp(page->page_pattern->regex, "") != 0)
                    get_nested_json(&contents, page->page_pattern->regex);
                if(0 < page->patterns->size)
                    replace_all(&contents, page->patterns, page->page_pattern->replace);

                write_file(output_file_path, contents, "w+");
            } else {
                printf("Empty content (extract_htmlpagedata)\n");
            }
        }
       
    }

    free(contents);
    free(parseContentPath);
    return 0;
}

int set_page_titlesRegex(STR_ARRAY *titlesRegex, char *filePath) {
    if(titlesRegex != NULL && filePath != NULL) {
        init_file_to_array(filePath, titlesRegex);
    }
    return 0;
}

int set_page_patterns(YPage *page, int type) {
    PATTERN * pattern;
    char **patterns = type == 0 ? DEFAULT_PATTERNS : CONTENTS_PATTERNS;

    if(page != NULL && 0 < page->patterns->size) {
        for(int i = 0; i < page->patterns->size; i++) {
            pattern = &(page->patterns)->patterns[i];
            set_pattern_value(pattern, patterns[i]);
        }
    }

    return 0;
}

int init_page_pattern_paramters(PAGEPATTERN *pattern) {
    if(pattern != NULL) {
        pattern->url = (char*)malloc(sizeof(*pattern->url));
        pattern->regex = (char*)malloc(sizeof(*pattern->regex));
        pattern->replace = (char*)malloc(sizeof(*pattern->replace));
    }
    return 0;
}

int set_page_pattern_url(PAGEPATTERN  *pattern, char *url) {
    char *new_url;

    if(pattern != NULL && url != NULL) {
        new_url = (char*) realloc(pattern->url, (strlen(url)+1) * sizeof(char));
        if(new_url != NULL) {
            sprintf(new_url, "%s", url);
            pattern->url = new_url;
        }
    }
    return 0;
}

int set_page_pattern_regex(PAGEPATTERN  *pattern, char *regex) {
    char *new_regex;

    if(pattern != NULL && regex != NULL) {
        new_regex = (char*) realloc(pattern->regex, (strlen(regex)+1) * sizeof(char));
        if(new_regex != NULL) {
            pattern->regex = new_regex;
            sprintf(pattern->regex, "%s", regex);
        }
    }
    return 0;
}

int set_page_pattern_replace(PAGEPATTERN  *pattern, char *replace) {
    char *new_replace;

    if(pattern != NULL && replace != NULL) {
        new_replace = (char*) realloc(pattern->replace, (strlen(replace)+1) * sizeof(char));
        if(new_replace != NULL) {
            sprintf(new_replace, "%s", replace);
            pattern->replace = new_replace;
        }
    }

    return 0;
}

int print_page_pattern(PAGEPATTERN *pattern) {
    if(pattern != NULL) {
        printf("PAGEPATTERN : {\n");
        printf("\t Url : %s\n", pattern->url);
        printf("\t Regex : %s\n", pattern->regex);
        printf("\t Replace : %s\n", pattern->replace);
        printf("}\n");
    }
    return 0;
}

int free_page_pattern(PAGEPATTERN *pattern) {
    if(pattern != NULL) {
        free(pattern->url);
        free(pattern->regex);
        free(pattern->replace);
    }
    free(pattern);
    return 0;
}

int init_yPage(YPage *page) {
    if(page != NULL) {
        page->type = 0;
        page->mongo_client = NULL;
        page->patterns = malloc(sizeof(*page->patterns));
        page->page_pattern = malloc(sizeof(*page->page_pattern));
        page->titlesRegex = malloc(sizeof(*page->titlesRegex));

        init_mongo_client(&(page->mongo_client));
        init_page_pattern_paramters(page->page_pattern);
        init_default_str_array_struct(page->titlesRegex);
        init_patterns(page->patterns, DEFAULT_PATTERNS_LEN);
    }
    return 0;
}

int free_yPage(YPage *page) {
    if(page != NULL) {
        mongoc_cleanup();
        free_patterns(page->patterns);
        free_page_pattern(page->page_pattern);
        free_mongo_client(page->mongo_client);
        free_str_array_struct(page->titlesRegex);
    }
    free(page);
    return 0;
}

int set_yPage(YPage *page, int type, char *url, char *replace, char *titlesRegexFilePath) {
    const char *regex = type == 0 ? "" : CONTENT_REGEX;
    if(page != NULL) {
        page->type = type;
        set_page_patterns(page, type);
        set_page_pattern_replace(page->page_pattern, replace);
        set_page_pattern_url(page->page_pattern, url);
        set_page_pattern_regex(page->page_pattern, (char*)regex);
        set_page_titlesRegex(page->titlesRegex, titlesRegexFilePath);
    }  
    return 0;
}

int print_page(YPage *page) {
    if(page != NULL) {
        printf("Page : {\n");
        printf("\t Type : %d,\n", page->type);
        printf("\t url : %s,\n", page->page_pattern->url);
        printf("\t regex : %s\n", page->page_pattern->regex);
        print_patterns(page->patterns);
        printf("}");
    }
    return 0;
}

int downloadPage_and_replace(char *parseContent, YPage *page) {
    char *downloadPageSrc = NULL; 
    get_pwd(&downloadPageSrc, DOWNLOAD_TEST_FILE);

    if(page != NULL && downloadPageSrc != NULL) {
        downloadPage_bycontains(&(page->page_pattern->url), downloadPageSrc, YINITDATA_VAR);
        extract_htmlpagedata(downloadPageSrc, parseContent, page);
        free(downloadPageSrc);
    }

    return 0;
}

int oversizejson_handler(char* parseFile) {
    char buffer[10];
    int file_count = 0;
    char *dirPath = NULL;
    char *errorFile = NULL;
    char fileName[50] = "/data/tabserrors/error";

    if(parseFile != NULL) {
        get_pwd(&dirPath,  "/data/tabserrors/");
        file_count =  cpt_files(dirPath);
        sprintf(buffer, "%d", file_count);
        strcat(fileName, buffer);

        get_pwd(&errorFile, fileName);
        copy(parseFile, errorFile);
        //printf("OverSize : %d, parseFile : %s, %s\n", size,  parseFile, fileName);
    }

    free(dirPath);
    free(errorFile);
    return 0;
}

int extract_target_json(char *contents, char *output, char *regex, char *replace, char *separator, int testjson) {
    struct json_object *json = NULL;

    if(contents != NULL && output != NULL) {
        //trim(&contents);
        get_nested_json(&contents, regex);
        replace_substring(&contents, replace, separator);
        write_file(output, contents, "w+");

        if(testjson) {
            detect_oversize_json(output, &json);
            //printf("VALUE : %s\n", json_object_get_string(json));
        }
    }

    json_object_put(json);
    return 0;
}

int extract_sub_json(char *outFilePath, int output_index, char *input_file, char *regex, char *replace, char *separator, int testjson, char **resFile) {
    char buffer[10];
    char fileName[50];
    char *outputFile = NULL;
    char *contents = (char*) calloc(2, sizeof(char));
    load_file(input_file, &contents);

    if(outFilePath != NULL && contents != NULL) {
        sprintf(fileName, "%s", outFilePath);
        sprintf(buffer, "%d", output_index);
        strcat(fileName, buffer);
        get_pwd(&outputFile, fileName);
        extract_target_json(contents, outputFile, regex, replace, separator, testjson);
        
        if(*resFile != NULL)
            sprintf(*resFile, "%s", outputFile);
    }

    free(outputFile);
    free(contents);

    return 0;
}

int fragments_json(char *input_file, int output_index) {
    char *contents = (char*) calloc(2, sizeof(char));
    char *pageFilePath = malloc(50 *sizeof(char));
    char *infosFilePath = malloc(50 *sizeof(char));
    char *secondaryFilePath = malloc(50 *sizeof(char));

    const char *results_regex = "\\{\"results.*secondaryResults";
    const char *infos_regex = "\\{\"videoPrimaryInfoRenderer.*videoSecondaryInfoRenderer";
    const char *secondaryResults_regex = "\\{\"secondaryResults.*\\{\"autoplay\":\\{\"sets\":";
    const char *video_page_regex = "\\{\"twoColumnWatchNextResults.*currentVideoEndpoint";
    const char *tabs_page_regex = "\\{\"richGridRenderer.*continuationItemRenderer";
    const char *tabs_page_shelfRenderer_regex = "\\{\"shelfRenderer.*playAllButton";

    if(input_file != NULL) {
        load_file(input_file, &contents);

        if(contents != NULL) {
            if(strstr(contents, "tabs") != NULL) {
                if(strstr(contents, "richGridRenderer") != NULL) {
                    extract_sub_json("/data/tabs/json", output_index, input_file, (char*)tabs_page_regex, ",\\{\"continuationItemRenderer$", "]}}", 1, &pageFilePath);
                } else if(strstr(contents, "shelfRenderer") != NULL) {
                    extract_sub_json("/data/tabs/json", output_index, input_file, (char*)tabs_page_shelfRenderer_regex, ",\"playAllButton$", "}}", 1, &pageFilePath);
                } else {
                    puts("tab oversizejson");
                    oversizejson_handler(input_file);
                }
            } else if(strstr(contents, "twoColumnWatchNextResults") != NULL) {
                extract_sub_json("/data/jsons/json", output_index, input_file, (char*)video_page_regex,  ",\"currentVideoEndpoint$", " ", 0, &pageFilePath);
                extract_sub_json("/data/results/json", output_index, pageFilePath, (char*)results_regex, ",\"secondaryResults\":\\{\"secondaryResults$", "}", 0, &secondaryFilePath);
                extract_sub_json("/data/infos/json", output_index, secondaryFilePath, (char*)infos_regex, ",\\{\"videoSecondaryInfoRenderer$", " ", 1, &infosFilePath);
                extract_sub_json("/data/secondaryResults/json", output_index, pageFilePath, (char *)secondaryResults_regex,  ",\"autoplay\":\\{\"autoplay\":\\{\"sets\":$", " ", 1, &secondaryFilePath);
            }
        }
    }

    free(contents);
    free(pageFilePath);
    free(infosFilePath);
    free(secondaryFilePath);
    return 0;
}

int json_mapping_to_director(DIRECTOR *director, struct json_object *director_json) {
    if(director != NULL && director_json != NULL) {
        printf("json_mapping_to_director");
        set_director(director, 
            "Director name","2014-01-01T08:15:39.736Z", 
            "2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z"
        );
    }
    return 0;
}

int json_mapping_to_studio(STUDIO *studio, struct json_object *studio_json) {
    if(studio != NULL && studio_json != NULL) {
        printf("json_mapping_to_studio");
        set_studio(studio, "Studio name", "Country", 
            "City", "Fonder","2014-01-01T08:15:39.736Z", 
            "2014-01-01T08:15:39.736Z", "2014-01-01T08:15:39.736Z"
        );
    }
    return 0;
}

int json_mapping_to_cast(CAST *cast, struct json_object *cast_json) {
    if(cast != NULL && cast_json != NULL) {
        printf("json_mapping_to_cast");
    }
    return 0;
}

int json_mapping_to_tags(STR_ARRAY *tags, struct json_object *tags_json) {
    if(tags != NULL && tags_json != NULL) {
        printf("json_mapping_to_tags");
        //resize_str_array_struct(tags, numb_tags);
        for(int i = 0; i <tags->length; i++) {
            set_str_value(&(tags->elements[i]), "Tag");
        }
    }
    return 0;
}

int json_mapping_player_to_video(VIDEO *video, struct json_object *player_json) {
    const char *title, *description, *viewCount, *date;
    struct json_object *titleObj, *descriptionObj, *viewCountObj, *dateObj;

    if(video != NULL && player_json != NULL) {
        titleObj = getObj_rec(player_json, VIDEO_PAGE_TITLE_FIELD);
        descriptionObj = getObj_rec(player_json, VIDEO_PAGE_DESCRIPTION_FIELD);
        viewCountObj = getObj_rec(player_json, VIDEO_VIEWCOUNT_FIELD);
        dateObj = getObj_rec(player_json, VIDEO_PAGE_DATE_FIELD);

        title = json_object_get_string(titleObj);
        description = json_object_get_string(descriptionObj);
        viewCount = json_object_get_string(viewCountObj);
        date =  json_object_get_string(dateObj);
        printf(" Player case : %s\n,%s, %s, %s\n", title, description, viewCount, date);
    }
    return 0;
}

int json_mapping_channels_tabs_data(struct json_object *videosContentObj) {
    unsigned int i;
    struct json_object *videoObj;
    struct json_object *channelIdObj, *titleObj, *subscriberCountObj, *channelUrlObj;
    //struct json_object *imgObj;

    if(videosContentObj != NULL) {
        puts("save_channels_tabs_data");
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

int json_mapping_player_channel(VIDEO *video, struct json_object *player_json) {
    const char *channelTitle, *channelImg, *channelUrl;
    struct json_object *channelTitleObj, *imgObj, *urlObj;

    if(video != NULL && player_json != NULL) {
        channelTitleObj = getObj_rec(player_json, VIDEO_PAGE_CHANNEL_TITLE_FIELD);
        imgObj = getObj_rec(player_json, VIDEO_PAGE_CHANNEL_IMG_FIELD);
        urlObj = getObj_rec(player_json, VIDEO_PAGE_CHANNEL_URL_FIELD);

        channelTitle = json_object_get_string(channelTitleObj);
        channelImg = json_object_get_string(imgObj);
        channelUrl = json_object_get_string(urlObj);
        printf("mapping_player_channel : %s\n,%s, %s\n", channelTitle, channelImg, channelUrl);
    }
    return 0;
}

int json_mapping_to_video(VIDEO *video, struct json_object *video_json, int type) {
    const char *title, *url, *length, *videoId;
    struct json_object *urlObj, *titleObj, *lengthObj, *videoIdObj;
    const char *summary = "", *category = "", *censor_rating= "";

    const char *urlField = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_URL_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_URL_FIELD : VIDEOS_PAGE_VIDEO_URL_FIELD);
    const char *titleField = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_TITLE_FIELD : VIDEOS_PAGE_VIDEO_TITLE_FIELD);
    const char *lengthField = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_LENGTH_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_LENGTH_FIELD : VIDEOS_PAGE_VIDEO_LENGTH_FIELD);
    const char *videoId_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_VIDEOID_FIELD : VIDEOS_PAGE_VIDEOID_FIELD);


    if(video != NULL && video_json != NULL) {
        urlObj = getObj_rec(video_json, (char*)urlField);
        titleObj = getObj_rec(video_json,(char*)titleField);
        lengthObj = getObj_rec(video_json, (char*)lengthField);
        videoIdObj = getObj_rec(video_json, (char *) videoId_field);

        url = json_object_get_string(urlObj);
        title = json_object_get_string(titleObj);
        length = json_object_get_string(lengthObj);
        videoId = json_object_get_string(videoIdObj);

        set_video(video, (char*)title, (char*) videoId, (char*)category, (char*)summary, (char*)url, (char*)length, (char*)censor_rating, "1970-01-01T10:42:00Z");
    }
    
    if(strcmp(video->title, "") == 0) {
        printf("%s, TYPE : %d\n", json_object_get_string(video_json), type);
    }

    return 0;
}

int json_mapping_to_videos(VIDEO_ARRAY *videos, struct json_object *videos_json, int type) {
    VIDEO *video;
    if(videos != NULL && videos_json != NULL) {
        for(int i = 0; i < videos->length; i++) {
            video = &(videos->elements[i]);
            json_mapping_to_video(video, videos_json, type);
        }
    }
    return 0;
}

int json_mapping_to_season(SEASON *season, struct json_object *season_json, int type) {
    const char *title, *videoId;
    struct json_object *titleObj, *videoIdObj;
    const char *title_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_TITLE_FIELD : VIDEOS_PAGE_VIDEO_TITLE_FIELD);
    const char *videoId_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_VIDEOID_FIELD : VIDEOS_PAGE_VIDEOID_FIELD);

    if(season != NULL && season_json != NULL) {
        titleObj = getObj_rec(season_json, (char *)title_field);
        videoIdObj = getObj_rec(season_json, (char *) videoId_field);

        title = json_object_get_string(titleObj);
        videoId = json_object_get_string(videoIdObj);

        set_seson(season, (char*)title, (char*)videoId, "1970-01-01T10:42:00Z", "", NULL);
        json_mapping_to_videos(season->videos, season_json, type);
    }

    return 0;
}

int json_mapping_to_seasons(SEASON_ARRAY *seasons, struct json_object *seasons_json, int type) {
    if(seasons != NULL && seasons_json != NULL) {
        for(int i = 0; i < seasons->length; i++) {
            json_mapping_to_season(&(seasons->elements[i]), seasons_json, type);
        }
    }
    return 0;
}

int json_mapping_to_keys_values(KEY_VALUE_ARRAY *array, struct json_object *video_json, int type) {
    int numb_of_keys = 3;
    const char *title, /*img,*/ *videoId, *viewCount;
    struct json_object *titleObj, /*imgObj,*/ *videoIdObj, *viewCountObj;
    const char *title_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_TITLE_FIELD : VIDEOS_PAGE_VIDEO_TITLE_FIELD);
    const char *videoId_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_VIDEOID_FIELD : VIDEOS_PAGE_VIDEOID_FIELD);
    const char *viewCount_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_VIEW_COUNT_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_VIEW_COUNT_FIELD : VIDEOS_PAGE_VIDEO_VIEWCOUNT_FIELD);

    if(video_json != NULL) {
        titleObj = getObj_rec(video_json, (char *)title_field);
        //imgObj = getObj_rec(video_json, VIDEO_PAGE_PLAYLIST_ITEM_IMG_FIELD);
        videoIdObj = getObj_rec(video_json, (char *) videoId_field);
        viewCountObj = getObj_rec(video_json, (char*)viewCount_field);

        title = json_object_get_string(titleObj);
        //img = json_object_get_string(imgObj);
        videoId = json_object_get_string(videoIdObj);
        viewCount = json_object_get_string(viewCountObj);

        resize_key_value_array_struct(array, numb_of_keys);
        set_key_value(&(array->elements[0]) , "title", (char*)title);
        set_key_value(&(array->elements[1]), "img", (char*)videoId/*(char*)img*/);
        //set_key_value(&(array->elements[2]), "videoId", (char*)videoId);
        set_key_value(&(array->elements[2]), "viewCount", (char*)viewCount);
        //set_key_value(&(array->elements[2]), "category", (char*)json_object_get_string(titleObj));
        //set_key_value(&(array->elements[3]), "summary", (char*)json_object_get_string(titleObj));
    }
    return 0;
}

int json_mapping_to_serie(SERIE *serie, struct json_object *video_json, int type) {
    if(video_json != NULL && serie != NULL) {
        json_mapping_to_keys_values(serie->key_value_array, video_json, type);
        set_serie_gender(serie, "Comedy");
        set_serie_category(serie, "Default");
        set_serie_country(serie, "CD");
        set_serie_year(serie, "1970-01-01T10:42:00Z");
        //json_mapping_to_director(serie->director, NULL);
        //json_mapping_to_director(serie->producer, NULL);
        //json_mapping_to_studio(serie->studio, NULL);
        //json_mapping_to_cast(serie->cast, NULL);
        //json_mapping_to_tags(serie->contentTag, NULL);
        json_mapping_to_seasons(serie->seasons, video_json, type);
    }
    return 0;
}

int is_matching_title(STR_ARRAY *titlesRegex, char *title) {
    int res = 0;

    if(titlesRegex != NULL && title != NULL) {
        //print_array_str(titlesRegex, "", "\t", "\t", "\t\t");
        for(int i = 0; i < titlesRegex->length; i++) {
            if(match_pattern(title, (titlesRegex->elements[i]).value)) {
                res = 1;
                break;
            }
        } 
    }

    return res;
}

int get_title_selector(char *title, bson_t **selector) {
    File *fifo = malloc(sizeof(*fifo));
    char *regex = (char*) calloc(1, sizeof(char));

    fifo_init(fifo);
    if(title != NULL) {
        get_match(title, "[a-zA-Z]{4,}", fifo);
        join_file_element(fifo, &regex, ".*", 1, -1);
        //printf("title : %s\n", title);
        //printf("REGEX : %s\n", regex);
        if(regex != NULL) {
            *selector = BCON_NEW("title", "{", "$regex", BCON_UTF8(regex), "$options", BCON_UTF8("i"),"}");
        }
    }
    free(regex);
    freeFile(fifo);
    return 0;
}

int get_selector_by_numb_of_match(char *key, char *value, char *pattern,  char *delimiter, bson_t **selector, int numb_match) {
    File *fifo = malloc(sizeof(*fifo));
    char *regex = (char*) calloc(1, sizeof(char));

    fifo_init(fifo);

    if(key != NULL && value != NULL && pattern != NULL && delimiter != NULL) {
        get_match(value, pattern, fifo);
        join_file_element(fifo, &regex, delimiter, 1, numb_match);
        if(regex != NULL) {
            *selector = BCON_NEW(key, "{", "$regex", BCON_UTF8(regex), "$options", BCON_UTF8("i"),"}");
        }
    }
    free(regex);
    freeFile(fifo);

    return 0;
}

int exist_serie_in_db(mongoc_client_t *client, char *title, SERIE *serie) {
    int res = 0;
    const char* db_name =  "maboke";
    bson_t *selector = NULL, *prefix_selector = NULL;
    const char *serie_collection = "serie", *search_collection = "search";

    if(title != NULL && client != NULL && serie != NULL) {
        get_title_selector(title, &selector);
        if(selector != NULL) {
            res = exist_document(client, selector, (char*)db_name, (char*)search_collection);
            if(res) { 
                //printf("Serie title : %s\n", title);
                res = find_serie(client, selector, (char*)db_name, (char*)serie_collection, serie);
                //print_serie(serie);
            } else {
                get_selector_by_numb_of_match("title", title, "[a-zA-Z]{4,}", ".*", &prefix_selector, 3);
                if(exist_document(client, prefix_selector, (char*)db_name, (char*)serie_collection))
                    res = -1;
            }
        }
    }

    bson_destroy(selector);
    bson_destroy(prefix_selector);
    //bson_free(selector);
    //bson_free(prefix_selector);
    return res;
}

int exist_title_in_collection(mongoc_client_t *client, char *title, char *db_name, char *collection) {
    int res = 0;
    bson_t *selector = NULL;

    if(title != NULL && client != NULL) {
        get_title_selector(title, &selector);
        if(selector != NULL) {
            res = exist_document(client, selector, db_name, collection);
        }
    }
    bson_destroy(selector);
    //bson_free(selector);
    return res;
}

int exist_url_in_collection(mongoc_client_t *client, char *url, char *db_name, char *collection) {
    int res = 0;
    bson_t *selector = NULL;
    
    if(url != NULL && client != NULL) {
        selector =  BCON_NEW("url", BCON_UTF8(url));
        if(selector != NULL) {
            res = exist_document(client, selector, db_name, collection);
        }
    }

    bson_free(selector);
    return res;
}

int print_serie_bson(bson_t *document) {
    char *str;
    if(document != NULL) {
        str = bson_as_canonical_extended_json(document, NULL);
        //str = bson_as_json(document, NULL);
        bson_free(str);
    }
    return 0;
}

int update_season_videos(mongoc_client_t *client,SERIE *serie, SEASON *season, struct json_object *video_json, char *title, int type) {
    VIDEO *video;
    int exist = 0;
    char *videoId = NULL;
    VIDEO_ARRAY *videos = season->videos;

    if(videos != NULL && video_json != NULL && title != NULL) {
        for(int i = 0; i < videos->length; i++) {
            video = &(videos->elements[i]);
            //printf("Title : %s, %s\n", video->title, title);
            if(strcmp(video->title, title) == 0) {
                exist = 1;
                break;
            }
        }

        if(!exist) {
            resize_video_array_struct(videos, videos->length+1);
            video =  &(videos->elements[videos->length-1]);
            if(video != NULL) {
                json_mapping_to_video(video, video_json, type);

                if(get_title_episode(title) < get_title_episode(season->title)) {
                    videoId = (char*) calloc(1, sizeof(char));
                    extraxt_url_videoId(video->url, &videoId);
                    set_season_title(season, title);
                    set_season_img(season, videoId);
                    if(season->number == 1 && videoId != NULL) {
                        //printf("VIDEOID : %s, %s\n", video->url, videoId); 
                        set_key_value_value(&(serie->key_value_array->elements[0]), title);
                        set_key_value_value(&(serie->key_value_array->elements[1]), videoId);
                    }
                    //print_serie(serie);
                }
                add_search_values_to_db(client, video, video_json, type);
            }
        }
    }

    free(videoId);
    return exist;
}

int update_serie(mongoc_client_t *client, SERIE *serie, struct json_object *video_json, char *title, int type) {
    SEASON *season;
    bson_t *selector = NULL;
    bson_t *document = bson_new();
    int videoExist = 0, existSeason = 0;
    const char *dbName = "maboke", *collection = "serie";

    if(serie != NULL && video_json != NULL && title != NULL) {
        for(int i = 0; i < serie->seasons->length; i++) {
            season = &(serie->seasons->elements[i]);
            printf("Title : %s\n", title);
            if(season->number == get_title_season(title)) {
                existSeason = 1;
                videoExist = update_season_videos(client, serie, season, video_json, title, type);
                break;
            }
        }

        if(!existSeason) {
            puts("No exist season");
            resize_season_array_struct(serie->seasons, serie->seasons->length+1, 1);
            season = &(serie->seasons->elements[serie->seasons->length-1]);
            if(season != NULL) {
                json_mapping_to_season(season, video_json, type);
            }
        }

        get_title_selector(title, &selector);
        if(selector != NULL && (!videoExist || !existSeason)) {
            serie_to_set_bson(&document, serie);
            update_document(client, (char*)dbName, (char*)collection, selector, document);
            //print_serie_bson(document);
            //print_serie(serie);
        }

        bson_free(selector);
        bson_destroy(document);
    }

    return 0;
}

int add_search_values_to_db(mongoc_client_t *client, VIDEO *video, struct json_object *video_json, int type) {
    bson_t *document = bson_new();
    struct json_object *videoIdObj;
    const char *dbName = "maboke", *collection = "search", *videoId = NULL;
    const char *videoId_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_VIDEOID_FIELD : VIDEOS_PAGE_VIDEOID_FIELD);

    if(video != NULL && video_json != NULL) {
        if((videoIdObj = getObj_rec(video_json, (char*)videoId_field)) != NULL) {
            if((videoId = json_object_get_string(videoIdObj)) != NULL) {
                search_to_bson(&document, video->title, (char *)videoId);
                insert_document(client, (char*)dbName, (char*)collection, document);
            }
        }
        //print_serie_bson(document);
    }

    bson_destroy(document);
    return 0;
}

int create_new_serie(mongoc_client_t *client, struct json_object *video_json, int type, char *dbName, char *collection, int index_title, char *state) {
    VIDEO *video;
    SEASON *season;
    bson_t *document = bson_new();
    SERIE *serie = malloc(sizeof(*serie));

    if(video_json != NULL && serie != NULL) {
        init_serie_default_parameters(serie);
        json_mapping_to_serie(serie, video_json, type);
        set_serie_state(serie, state);
        serie_to_bson(&document, serie);
        insert_document(client, (char*)dbName, (char*)collection, document);
        
        if((season=&(serie->seasons->elements[0])) != NULL && index_title) {
            if((video = &(season->videos->elements[0])) != NULL) {
                add_search_values_to_db(client, video, video_json, type);
            }
        }
        //print_serie(serie);
        //print_serie_bson(document);
    }

    bson_destroy(document);
    free_serie(serie);
    return 0;
}

int add_url_to_file(File *urls_fifo, struct json_object *video_json, int type) {
    const char *videoId, *channelUrlId;
    struct json_object *videoIdObj, *channelUrlObj;
    char *url = (char*) calloc(100, sizeof(char));
    char *channelUrl = (char*) calloc(100, sizeof(char));
    const char *channel_url_field =  type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_CHANNEL_URL_FIELD : NULL;
    const char *videoId_field = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD : (type == 1 ? CHANNEL_PAGE_HOME_ITEM_VIDEOID_FIELD : VIDEOS_PAGE_VIDEO_URL_FIELD);

    if(urls_fifo != NULL && video_json != NULL && url != NULL) {
        videoIdObj = getObj_rec(video_json, (char*)videoId_field);
        videoId = json_object_get_string(videoIdObj);
        if(videoId != NULL) {
            strcat(url, "https://www.youtube.com/watch?v=");
            strcat(url, videoId);
            //printf("VideoId : %s\n", url);
            push(urls_fifo, url);
        }

        if(channel_url_field != NULL) {
            channelUrlObj = getObj_rec(video_json, (char *)channel_url_field);
            if((channelUrlId = json_object_get_string(channelUrlObj)) != NULL) {
                strcat(channelUrl, "https://www.youtube.com");
                strcat(channelUrl, channelUrlId);
                //printf("Url : %s\n", channelUrl);
                push(urls_fifo, channelUrl);
                strcat(channelUrl, "/videos"); 
                //printf("Url : %s\n", channelUrl);
                push(urls_fifo, channelUrl);
            }
        }
    }

    free(url);
    free(channelUrl);
    return 0;
}

int json_video_handler(YPage *page, struct json_object *video_json, char *title,  File *urls_fifo, int type) {
    int exist = 0;
    SERIE *serie = NULL;
    const char *dbName = "maboke", *serie_collection = "serie";

    if(page != NULL && video_json != NULL && title != NULL && is_matching_title(page->titlesRegex, title)) {
        serie = (SERIE *) calloc(1, sizeof(*serie));
        init_serie_default_parameters(serie);

        if((exist = exist_serie_in_db(page->mongo_client, title, serie)) == 1) {
            //puts("Update");
            update_serie(page->mongo_client, serie, video_json, title, type);
        } else if(exist == 0) {
            create_new_serie(page->mongo_client, video_json, type, (char *) dbName, (char *)serie_collection, 1, "match");
        } else if(exist == -1 && !exist_title_in_collection(page->mongo_client, title, (char*)dbName, (char *)serie_collection)) {
            //puts("No match");
            create_new_serie(page->mongo_client, video_json, type, (char *)dbName, (char *)serie_collection, 0, "no match");
        }
        add_url_to_file(urls_fifo, video_json, page->type);
    } /* else {
        logsFile
    }*/
    free_serie(serie);
    return 0;
}

int file_to_json(struct json_object **json, char *filePath, int output_index) {
    char buffer[10];
    char fileName[50];
    char *outputFile = NULL;

    if(filePath != NULL) {
        sprintf(fileName, "%s", filePath);
        sprintf(buffer, "%d", output_index);
        strcat(fileName, buffer);
        get_pwd(&outputFile, fileName);
        detect_oversize_json(outputFile, json);
    }

    free(outputFile);
    return 0;
}

int save_youtube_page_data(YPage *page, File *urls_fifo, int output_index) {
    const char *title;
    struct json_object *json = NULL;
    struct json_object *videos_json;
    struct json_object *video_json, *titleObj;

    file_to_json(&json, "/data/secondaryResults/json", output_index);

    if(json != NULL && page != NULL && urls_fifo != NULL) {
        videos_json = getObj_rec(json, VIDEO_PAGE_ROOT_FIELD);

        if(videos_json != NULL) {
            for(int i = 0; i < json_object_array_length(videos_json); i++) {
		        video_json = json_object_array_get_idx(videos_json, i);
                titleObj = getObj_rec(video_json, TITLE_FIELD);

                if((title = json_object_get_string(titleObj)) != NULL)
                    json_video_handler(page, video_json, (char*)title, urls_fifo, page->type);
	        }
        }
    }
    json_object_put(json);
    return 0;
}

int channel_home_page_videos(struct json_object *contents_json, YPage *page, File *urls_fifo) {
    const char *title;
    int size = 0, videosIndex = 0;
    struct json_object *videos_json, *video_json;
    struct json_object *item, *titleObj;

    if(contents_json != NULL) {
        size = json_object_array_length(contents_json);
        videosIndex = size == 1 ? 0 : 1;
        item = json_object_array_get_idx(contents_json, videosIndex);

        if(item != NULL) {
            if((videos_json =  getObj_rec(item, CHANNEL_PAGE_HOME_ITEMS_FIELD)) != NULL) {
                for(int i = 0; i < json_object_array_length(videos_json); i++) {
                    video_json = json_object_array_get_idx(videos_json, i);
                    if((titleObj = getObj_rec(video_json, CHANNEL_PAGE_HOME_ITEM_TITLE_FIELD)) != NULL) {
                        if((title = json_object_get_string(titleObj)) != NULL)
                            json_video_handler(page, video_json, (char*)title, urls_fifo, page->type);
                    }
                }
            }
            //printf("%s\n", json_object_get_string(item));
        }
    }
    return 0;
}

int channel_videos_page(struct json_object *videos_json, YPage *page, File *urls_fifo) {
    const char *title;
    struct json_object *video_json,  *titleObj;

    if(videos_json != NULL) {
        for(int i = 0; i < json_object_array_length(videos_json); i++) {
            video_json = json_object_array_get_idx(videos_json, i);
            if((titleObj = getObj_rec(video_json,  VIDEOS_PAGE_VIDEO_TITLE_FIELD)) != NULL) {
                if((title = json_object_get_string(titleObj)) != NULL)
                    json_video_handler(page, video_json, (char*)title, urls_fifo, 2);
            }
        }
    }

    return 0;
}

int save_channel_page_data(YPage *page, File *urls_fifo, int output_index) {
    struct json_object *json = NULL;
    struct json_object *contents;

    file_to_json(&json, "/data/tabs/json", output_index);
    if(page != NULL && urls_fifo != NULL && json != NULL) {
        puts("save_channel_page_data(");
        //"/tabRenderer/content/sectionListRenderer/contents/0/itemSectionRenderer/contents/0/gridRenderer/items"
        //if((contents = getObj_rec(tabObj, CHANNELS_PAGE_TAB_CONTENTS_FIELD)) != NULL)
        //    json_mapping_channels_tabs_data(contents);

        //"/tabRenderer/content/sectionListRenderer/contents"
        //else if((contents = getObj_rec(tabObj, CHANNEL_PAGE_HOME_TAB_CONTENTS_FIELD)) != NULL)
        //    channel_home_page_videos(contents, page, urls_fifo);

        //"/richGridRenderer/contents"
        if((contents = getObj_rec(json, CHANNEL_PAGE_VIDEOS_TAB_CONTENTS_FIELD)) != NULL)
            channel_videos_page(contents, page, urls_fifo);
    }

    json_object_put(json);
    return 0;
}

int cpt_dir_contents(dirPath) {
    int cpt = 0;
    char *dir_abs = NULL;

    if(dirPath != NULL) {
        get_pwd(&dir_abs, dirPath);
        cpt = cpt_files(dir_abs);
    }

    free(dir_abs);
    return cpt;
}

int pages_handler(YPage *page, char *url, char* parseFile, File *urls_fifo) {
    long size = 0;
    int output_index = 0;
    bson_t *document = bson_new(); 
    //struct json_object *json = NULL;
    const char *dbName = "maboke", *collection = "urls";

    if(page != NULL && url != NULL && parseFile != NULL && !exist_url_in_collection(page->mongo_client, url, (char*)dbName, (char*)collection)) {
        set_page_pattern_url(page->page_pattern, url);
        downloadPage_and_replace(parseFile, page);
        //size = file_tojson(parseFile, &json);

        if(page->type == 0) {
            output_index = cpt_dir_contents("/data/secondaryResults/");
            fragments_json(parseFile, output_index);
            save_youtube_page_data(page, urls_fifo, output_index);
        } else if(page->type == 1) {
            output_index = cpt_dir_contents("/data/tabs/");
            fragments_json(parseFile, output_index);
            save_channel_page_data(page, urls_fifo, output_index);
        }
        url_to_bson(&document, url);
        insert_document(page->mongo_client, (char*)dbName, (char*)collection, document);
    }

    //json_object_put(json);
    bson_destroy(document);
    return 0;
}

int detect_oversize_pages() {
    //"/contents/twoColumnWatchNextResults/secondaryResults/secondaryResults/results"
    //"/tabRenderer/content/sectionListRenderer/contents/0/itemSectionRenderer/contents/0/gridRenderer/items"
    //"/tabRenderer/content/sectionListRenderer/contents"
    //"/tabRenderer/content/richGridRenderer/contents"    
    for(int i = 1; i < 17; i++) {
        char buffer[10];
        char *errorFile = NULL;
        char fileName[50] = "/data/errors/error";
        sprintf(buffer, "%d", i);
        strcat(fileName, buffer);
        get_pwd(&errorFile, fileName);
        fragments_json(errorFile, i);
        //printf("FileName : %s\n", errorFile);
        free(errorFile);
    }
    return 0;
}