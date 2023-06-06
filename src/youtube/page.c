#include "./../../include/youtube/page.h"

int extract_htmlpagedata(char *html_file_path, char *output_file_path, YPage *page) {
    char *contents;
    char *parseContentPath = NULL; 

    if(html_file_path != NULL) {
        parseYFile(html_file_path);
        contents = (char*) malloc(sizeof(char));        
        get_absolutePath(YINITDATA_FILE_PATH, &parseContentPath);

        if(parseContentPath != NULL && output_file_path != NULL) {
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {
                trim(&contents);
               
                if(strcmp(page->page_pattern->regex, "") != 0)
                    get_nested_json(&contents, page->page_pattern->regex);
                 
                if(0 < page->patterns->size)
                    replace_all(&contents, page->patterns, page->page_pattern->replace);

                appendStrToFile(output_file_path, contents);
                free(contents);
            } else {
                printf("Empty content (extract_htmlpagedata)\n");
            }

            free(parseContentPath);
        }
    }

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
        //extract_htmlpagedata(downloadPageSrc, parseContent, page);
        free(downloadPageSrc);
    }

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
    const char *title, *url, *length;
    struct json_object *urlObj, *titleObj, *lengthObj;
    const char *summary = "", *category = "", *censor_rating= "";

    const char *urlField = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_URL_FIELD : VIDEO_PAGE_PLAYLIST_ITEM_URL_FIELD;
    const char *titleField = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD : VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD;
    const char *lengthField = type == 0 ? VIDEO_PAGE_PLAYLIST_ITEM_LENGTH_FIELD : VIDEO_PAGE_PLAYLIST_ITEM_LENGTH_FIELD;
    
    if(video != NULL && video_json != NULL) {
        urlObj = getObj_rec(video_json, (char*)urlField);
        titleObj = getObj_rec(video_json,(char*)titleField);
        lengthObj = getObj_rec(video_json, (char*)lengthField);
        
        url = json_object_get_string(urlObj);
        title = json_object_get_string(titleObj);
        length = json_object_get_string(lengthObj);
        //printf("json_mapping_to_video : %s, %s\n", url, title); 
        set_video(video, (char*)title, (char*)category, (char*)summary, (char*)url, (char*)length, (char*)censor_rating);
    }
    return 0;
}

int json_mapping_to_videos(VIDEO_ARRAY *videos, struct json_object *videos_json, int type) {
    VIDEO *video;
    if(videos != NULL && videos_json != NULL) {
        //printf("json_mapping_to_videos\n"); 
        for(int i = 0; i < videos->length; i++) {
            video = &(videos->elements[i]);
            json_mapping_to_video(video, videos_json, type);
        }
    }
    return 0;
}

int json_mapping_to_season(SEASON *season, struct json_object *season_json, int type) {
    const char *title;
    struct json_object *titleObj;

    if(season != NULL && season_json != NULL) {
        //printf("json_mapping_to_season\n");
        titleObj = getObj_rec(season_json, VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD);
        title = json_object_get_string(titleObj);
        set_seson(season, (char*)title, "", "", NULL);
        json_mapping_to_videos(season->videos, season_json, type);
    }
    return 0;
}

int json_mapping_to_seasons(SEASON_ARRAY *seasons, struct json_object *seasons_json, int type) {
    if(seasons != NULL && seasons_json != NULL) {
        //printf("json_mapping_to_seasons\n");
        for(int i = 0; i < seasons->length; i++) {
            json_mapping_to_season(&(seasons->elements[i]), seasons_json, type);
        }
    }
    return 0;
}

int json_mapping_to_keys_values(KEY_VALUE_ARRAY *array, struct json_object *video_json) {
    int numb_of_keys = 3;
    const char *title, /*img,*/ *videoId, *viewCount;
    struct json_object *titleObj, /*imgObj,*/ *videoIdObj, *viewCountObj;

    if(video_json != NULL) {
        titleObj = getObj_rec(video_json, VIDEO_PAGE_PLAYLIST_ITEM_TITLE_FIELD);
        //imgObj = getObj_rec(video_json, VIDEO_PAGE_PLAYLIST_ITEM_IMG_FIELD);
        videoIdObj = getObj_rec(video_json, VIDEO_PAGE_PLAYLIST_ITEM_VIDEOID_FIELD);
        viewCountObj = getObj_rec(video_json, VIDEO_PAGE_PLAYLIST_ITEM_VIEW_COUNT_FIELD);

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
        json_mapping_to_keys_values(serie->key_value_array, video_json);
        //set_serie_year(serie, "");
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
    char *regex = NULL;
    File *fifo = malloc(sizeof(*fifo));

    fifo_init(fifo);
    if(title != NULL) {
        get_match(title, "[^0-9 \n]+", fifo);
        join_file_element(fifo, &regex, ".*", 1);
        //printf("Regex : %s, %s\n", regex, title);
        if(regex != NULL) {
            *selector =  BCON_NEW(
                "title", "{",
                    "$regex", BCON_UTF8(regex),
                    "$options", BCON_UTF8("i"),
                "}"
            );
        }
    }
    free(regex);
    freeFile(fifo);
    return 0;
}

int exist_title_in_db(mongoc_client_t *client, char *title, SERIE *serie) {
    int res = 0;
    bson_t *selector = NULL;
    const char* db_name =  "maboke";
    const char* document_name = "serie";

    if(title != NULL && client != NULL && serie != NULL) {
        get_title_selector(title, &selector);
        if(selector != NULL) {
            res = exist_serie(client, selector, (char*)db_name, (char*)document_name, serie);
            //if(res)
            //  print_serie(serie);
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
        printf("NO EXIST : %s\n", str);
        bson_free(str);
    }
    return 0;
}

int update_season_videos(VIDEO_ARRAY *videos, struct json_object *video_json, char *title) {
    VIDEO *video;
    int exist = 0;

    if(videos != NULL && video_json != NULL && title != NULL) {
        for(int i = 0; i < videos->length; i++) {
            video = &(videos->elements[i]);
            if(strcmp(video->title, title) == 0) {
                exist = 1;
                break;
            }
        }

        if(!exist) {
            resize_video_array_struct(videos, videos->length+1);
            video =  &(videos->elements[videos->length-1]);
            if(video != NULL)
                json_mapping_to_video(video, video_json, 0);
            puts("Add video");
        }
    }

    return exist;
}

int update_serie(mongoc_client_t *client, SERIE *serie, struct json_object *video_json, char *title) {
    SEASON *season;
    bson_t *selector = NULL;
    bson_t *document = bson_new();
    int videoExist = 0, existSeason = 0;
    const char *dbName = "maboke", *collection = "serie";

    if(serie != NULL && video_json != NULL && title != NULL) {
        for(int i = 0; i < serie->seasons->length; i++) {
            season = &(serie->seasons->elements[i]);

            if(season->number == get_title_season(title)) {
                //season->videos
                //puts("update_serie");
                existSeason = 1;
                videoExist = update_season_videos(season->videos, video_json, title);
                break;
            }
        }

        if(existSeason && !videoExist && season != NULL && get_title_episode(title) < get_title_episode(season->title)) {
            set_season_title(season, title);
            if(season->number == 1)
                set_key_value_value(&(serie->key_value_array->elements[0]), title);
            //print_serie(serie);
        } else if(!existSeason) {
            resize_season_array_struct(serie->seasons, serie->seasons->length+1, 1);
            season = &(serie->seasons->elements[serie->seasons->length-1]);
            json_mapping_to_video(&(season->videos->elements[0]), video_json, 0);
            //print_serie(serie);
        }

        get_title_selector(title, &selector);

        if(selector != NULL) {
            serie_to_set_bson(&document, serie);
            update_document(client, (char*)dbName, (char*)collection, selector, document);
            print_serie_bson(document);
            //print_serie(serie);
        }

        bson_free(selector);
        bson_destroy(document);
    }

    return 0;
}

int create_new_serie(mongoc_client_t *client, struct json_object *video_json, int type) {
    bson_t *document = bson_new();
    SERIE *serie = malloc(sizeof(*serie));
    const char *dbName = "maboke", *collection = "serie";

    if(video_json != NULL && serie != NULL) {
        init_serie_default_parameters(serie);
        json_mapping_to_serie(serie, video_json, type);
        serie_to_bson(&document, serie);
        
        insert_document(client, (char*)dbName, (char*)collection, document);
        //print_serie_bson(document);
        //print_serie(serie);
    }

    bson_destroy(document);
    free_serie(serie);
    return 0;
}

int save_youtube_page_data(struct json_object *json, YPage *page) {
    const char *title;
    SERIE *serie = NULL;
    struct json_object *video_json, *titleObj;
    struct json_object *videos_josn/*, *player_json*/;
    
    if(json != NULL && page != NULL) {
        videos_josn = getObj_rec(json, VIDEO_PAGE_ROOT_FIELD);
        //player_json = getObj_rec(json, VIDEO_PAGE_CHANNEL_ROOT_FIELD);
        ///printf("save_youtube_page_data(1) : %s\n", json_object_get_string(video_json));
        if(videos_josn != NULL) {
            for(int i = 0; i < json_object_array_length(videos_josn); i++) {
		        video_json = json_object_array_get_idx(videos_josn, i);
                titleObj = getObj_rec(video_json, TITLE_FIELD);
                title = json_object_get_string(titleObj);

                if(is_matching_title(page->titlesRegex, (char*)title)) {
                    serie = malloc(sizeof(*serie));
                    init_serie_default_parameters(serie);
                    if(exist_title_in_db(page->mongo_client, (char*)title, serie)) {
                        update_serie(page->mongo_client, serie, video_json, (char*)title);
                    } else {
                        create_new_serie(page->mongo_client, video_json, 0);
                    }
                    free_serie(serie);
                    serie = NULL;
                }
                /*if(video != NULL && player_json != NULL) {
                    json_mapping_player_to_video(video, player_json);
                    json_mapping_player_channel(video, player_json);
                }*/
	        }
        }
    }
    return 0;
}

int videopage_handler(YPage *page, char *url, char* parseFile) {
    struct json_object *json = NULL;

    if(page != NULL && url != NULL && parseFile != NULL) {
        set_page_pattern_url(page->page_pattern, url);
        downloadPage_and_replace(parseFile, page);
        //file_tojson(parseFile, &json);
        //save_youtube_page_data(json, page);
    }

    json_object_put(json);
    return 0;
}