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
                if(page->page_pattern->regex != NULL)
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

int set_page_titlesRegex(STR_ARRAY **titlesRegex, char *filePath) {
    *titlesRegex = NULL;

    if(filePath != NULL) {
        init_file_to_array(filePath, &(*titlesRegex));
    }

    return 0;
}

int set_page_patterns(YPage *page, int type) {
    PATTERN * pattern;
    char **patterns = type == 0 ? DEFAULT_PATTERNS : CONTENTS_PATTERNS;

    if(page != NULL) {
        for(int i = 0; i < page->patterns->size; i++) {
            pattern = &(page->patterns)->patterns[i];
            set_pattern_value(pattern, patterns[i]);
        }
    }

    return 0;
}

int init_page_pattern_paramters(PAGEPATTERN **pattern) {
    if(*pattern == NULL)
        *pattern = malloc(sizeof(*pattern));

    if(pattern != NULL) {
        (*pattern)->url = (char*)malloc(sizeof(char));
        (*pattern)->regex = (char*)malloc(sizeof(char));
        (*pattern)->replace = (char*)malloc(sizeof(char));
    }
    return 0;
}

int set_page_pattern_url(PAGEPATTERN  *pattern, char *url) {
    char *new_url;

    if(pattern != NULL && url != NULL) {
        new_url = (char*) realloc(pattern->url, (strlen(url)+1) * sizeof(char));
        if(new_url != NULL) {
            pattern->url = new_url;
            sprintf(pattern->url, "%s", url);
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
            pattern->replace = new_replace;
            sprintf(pattern->replace, "%s", replace);
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
        free(pattern);
    }
    return 0;
}

int init_yPage(YPage **page) {
    size_t patterns_len = 0 ? DEFAULT_PATTERNS_LEN : CONTENTS_PATTERNS_LEN;

    if(*page == NULL)
        *page = malloc(sizeof(*page));

    if(*page != NULL) {
        (*page)->type = 0;
        (*page)->mongo_client = NULL;
        (*page)->titlesRegex = NULL;
        (*page)->patterns =  malloc(sizeof(PATTERNS *));
        (*page)->page_pattern = malloc(sizeof(PAGEPATTERN *));

        init_page_pattern_paramters(&((*page)->page_pattern));
        init_patterns((*page)->patterns, patterns_len);
        init_mongo_client(&((*page)->mongo_client));
    }
    return 0;
}

int set_yPage(YPage *page, int type, char *url, char *replace, char *titlesRegexFilePath) {
    if(page != NULL) {
        set_page_patterns(page, type);
        set_page_pattern_replace(page->page_pattern, replace);
        set_page_pattern_url(page->page_pattern, url);
        set_page_pattern_regex(page->page_pattern, CONTENT_REGEX);
        set_page_titlesRegex(&(page->titlesRegex), titlesRegexFilePath);
    }  
    return 0;
}

int free_yPage(YPage *page) {
    if(page != NULL) {
        free_patterns(page->patterns);
        free_page_pattern(page->page_pattern);
        free_str_array_struct(page->titlesRegex);
        free_mongo_client(page->mongo_client);
        mongoc_cleanup();
        free(page);
    }
    return 0;
}

int print_page(YPage *page) {
    if(page != NULL) {
        printf("Page : {\n");
        printf("\t url : %s\n", page->page_pattern->url);
        printf("\t regex : %s\n", page->page_pattern->regex);
        print_patterns(page->patterns);
        printf("}");
    }
    return 0;
}

int downloadPage_and_replace(char *parseContent, YPage *page) {
    char *downloadPageSrc = NULL; 
    get_pwd(&downloadPageSrc, DOWNLOAD_TEST_FILE);

    if(downloadPageSrc != NULL) {
        downloadPage_bycontains(&(page->page_pattern->url), downloadPageSrc, YINITDATA_VAR);
        extract_htmlpagedata(downloadPageSrc, parseContent, page);
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
        for(int i = 0; i <tags->length; i++) {
            set_str_value(&(tags->elements[i]), "Tag");
        }
    }
    return 0;
}

int json_mapping_to_video(VIDEO *video, struct json_object *video_json) {
    if(video != NULL && video_json != NULL) {
        printf("json_mapping_to_video");
        set_video(video, "title", "category", "summary", "url", "length", "censor_rating");
    }
    return 0;
}

int json_mapping_to_videos(VIDEO_ARRAY *videos, struct json_object *videos_json) {
    if(videos != NULL && videos_json != NULL) {
        printf("json_mapping_to_videos");
        for(int i = 0; i < videos->length; i++) {
            set_video(&(videos->elements[i]), "title", "category", "summary", "url", "length", "censor_rating");
        }
    }
    return 0;
}

int json_mapping_to_season(SEASON *season, struct json_object *season_json) {
    if(season != NULL && season_json != NULL) {
        printf("json_mapping_to_seasons");
        //VIDEO_ARRAY *videos
        set_seson(season, "title", "date", "summary", NULL);
    }
    return 0;
}

int json_mapping_to_seasons(SEASON_ARRAY *seasons, struct json_object *seasons_json) {
    if(seasons != NULL && seasons_json != NULL) {
        printf("json_mapping_to_seasons");
        for(int i = 0; i < seasons->length; i++) {
            json_mapping_to_season(&(seasons->elements[i]), seasons_json);
        }
    }
    return 0;
}

int json_mapping_to_keys_values(KEY_VALUE_ARRAY *array, struct json_object *video_json) {
    struct json_object *titleObj, *imgObj/*, *categoryObj, *summaryObj, *videoIdObj*/;

    if(video_json != NULL) {
        titleObj = getObj_rec(video_json, TITLE_FIELD);
        imgObj = getObj_rec(video_json, IMG_FIELD);
        //videoIdObj = getObj_rec(video, VIDEOID_FIELD);

        set_key_value(&(array->elements[0]) , "title", (char*)json_object_get_string(titleObj));
        set_key_value(&(array->elements[1]), "img", (char*)json_object_get_string(imgObj));
        //set_key_value(&(array->elements[2]), "category", (char*)json_object_get_string(titleObj));
        //set_key_value(&(array->elements[3]), "summary", (char*)json_object_get_string(titleObj));

    }
    return 0;
}

int json_mapping_to_serie(SERIE *serie, struct json_object *video_json) {
    //SERIE *serie = malloc(sizeof(*serie));
    if(video_json != NULL && serie != NULL) {
        init_serie_struct(serie, 4, 1, 1, 1);
        json_mapping_to_keys_values(serie->key_value_array, video_json);
        set_serie_year(serie, "2014-01-01T08:15:39.736Z");
        json_mapping_to_director(serie->director, NULL);
        json_mapping_to_director(serie->producer, NULL);
        json_mapping_to_studio(serie->studio, NULL);
        //json_mapping_to_cast(serie->cast, NULL);
        json_mapping_to_tags(serie->contentTag, NULL);
        json_mapping_to_seasons(serie->seasons, NULL);
    }
    //free_serie(serie);
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

int exist_title_in_db(mongoc_client_t *client, char *title) {
    int res = 0;
    char *regex = NULL;
    bson_t *selector = NULL;
    const char* db_name =  "maboke";
    const char* document_name = "serie";
    File *fifo = malloc(sizeof(*fifo));
    //SERIE *serie = malloc(sizeof(*serie));

    fifo_init(fifo);
    if(title != NULL && client != NULL) {
        get_match(title, "[A-Za-z]+[ ]+[A-Za-z]+", fifo);
        join_file_element(fifo, &regex, ".*", 1);
        //printf("Regex : %s\n", regex);
        if(regex != NULL) {
            selector =  BCON_NEW(
                "title", "{",
                    "$regex", BCON_UTF8(regex),
                    "$options", BCON_UTF8("i"),
                "}"
            );
            //print_bson(selector);
            res = exist_serie(client, selector, (char*)db_name, (char*)document_name);
            //print_serie(serie);
            //"maboke", "serie"
        }
    }

    free(regex);
    freeFile(fifo);
    //free_serie(serie);
    bson_destroy(selector);
    return res;
}

int create_new_serie(struct json_object *video_json) {
    SERIE *serie = NULL;

    if(video_json != NULL) {
        serie = malloc(sizeof(*serie));

        if(serie != NULL) {
            json_mapping_to_serie(serie, video_json);
            //print_serie(serie);                
        }
    }

    free_serie(serie);
    return 0;
}

int save_youtube_page_data(struct json_object *json, YPage *page) {
    unsigned int i;
    const char *title;
    struct json_object *videos_josn;
    struct json_object *video_json, *titleObj;

    if(json != NULL && page != NULL) {
        videos_josn = getObj_rec(json, YRESULTS_FIELDS);
        if(videos_josn != NULL) {
            for(i = 0; i < json_object_array_length(videos_josn); i++) {
		        video_json = json_object_array_get_idx(videos_josn, i);
                titleObj = getObj_rec(video_json, TITLE_FIELD);
                title = json_object_get_string(titleObj);

                if(is_matching_title(page->titlesRegex, (char*)title)) {
                    //save_video(video, json_object_get_string(titleObj));
                    if(exist_title_in_db(page->mongo_client, (char*)title)) {
                        printf("Exist : %s\n", title);
                    } else {
                        create_new_serie(video_json);
                    }
                }
	        }
        }
    }
    return 0;
}

int videopage_handler(YPage *page, char *url, char* parseFile) {
    struct json_object *json = NULL;
    if(url != NULL) {
        //printf("VideoPage : %s\n", url);
        set_page_pattern_url(page->page_pattern, url);
        //print_page(page);
        downloadPage_and_replace(parseFile, page);
        file_tojson(parseFile, &json);
        save_youtube_page_data(json, page);
    }

    json_object_put(json);

    return 0;
}