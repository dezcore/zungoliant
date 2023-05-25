#include "./../../include/youtube/page.h"

int print_patterns(char **patterns, size_t len) {
    if(patterns != NULL) {
        for(int i = 0; i < len; i++) {
            if(patterns[i] != NULL) {
                printf("Pattern : %s\n", patterns[i]);
            }
        }
    }
    return 0;
}

int print_page(YPage *page) {
    if(page != NULL) {
        printf("Url : %s, regex : %s\n", page->url, page->regex);
        print_patterns(page->patterns, page->patterns_len);
    }
    return 0;
}

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
                if(page->regex != NULL)
                    get_nested_json(&contents, page->regex);

                if(0 < page->patterns_len)
                    replace_all(&contents, page->patterns, page->replace, page->patterns_len);

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

char** init_patterns(char **defaultPatterns, size_t len) {
    char **patterns = malloc(len * sizeof(char*));

    if(defaultPatterns != NULL) {
        for(int i = 0; i < len; i++) {
            patterns[i] = (char*) calloc(DEFAULT_STR_LEN, sizeof(char));
            if(patterns[i] != NULL) {
                sprintf(patterns[i], "%s", defaultPatterns[i]);
            }
        }
    }

    return patterns;
}

int init_yPage(YPage *page, int type, char *url, char *replace) {
    char **patterns = type == 0 ? DEFAULT_PATTERNS : CONTENTS_PATTERNS;
    size_t patterns_len = 0 ? DEFAULT_PATTERNS_LEN : CONTENTS_PATTERNS_LEN;
    page->patterns_len = patterns_len;
    page->patterns = init_patterns(patterns, patterns_len); 
    page->url = (char*) calloc(DEFAULT_STR_LEN, sizeof(char));
    page->replace = (char*) calloc(DEFAULT_STR_LEN, sizeof(char));
    page->regex = type == 0 ? NULL : (char*) calloc((strlen(CONTENT_REGEX)+1), sizeof(char));

    if(url != NULL && page->replace != NULL) {
        sprintf(page->url, "%s", url);
        sprintf(page->replace, "%s", replace);
    }

    if(page->regex != NULL)
        sprintf(page->regex, "%s", CONTENT_REGEX);
    
    return 0;
}

int set_url(YPage *page, char *url) {

    if(page != NULL && url != NULL) {
        //page->url = (char*) realloc(page->url, (strlen(url)) * sizeof(char));
        //strcpy(page->url, url);
        sprintf(page->url, "%s", url);
    }
    
    return 0;
}

int free_patterns(char **patterns, size_t len) {
    if(patterns != NULL) {
        for(int i = 0; i < len; i++) {
            free(patterns[i]);
        }
        free(patterns);
    }
    return 0;
}

int free_yPage(YPage *page) {
    free(page->url);
    free(page->replace);
    free_patterns(page->patterns, page->patterns_len);
    if(page->regex != NULL)
        free(page->regex);
    json_object_put(page->json);
    free(page);
    return 0;
}

int downloadPage_and_replace(char *parseContent, YPage *page) {
    char *downloadPageSrc = NULL; 
    get_pwd(&downloadPageSrc, DOWNLOAD_TEST_FILE);

    if(downloadPageSrc != NULL) {
        downloadPage_bycontains(&(page->url), downloadPageSrc, YINITDATA_VAR);
        extract_htmlpagedata(downloadPageSrc, parseContent, page);
        free(downloadPageSrc);
    }

    return 0;
}

int save_data(struct json_object *json, STR_ARRAY *titlesRegex) {
    unsigned int i;
    struct json_object *results;
    struct json_object *video, *titleObj;

    if(json != NULL) {
        results = getObj_rec(json, YRESULTS_FIELDS);
        if(results != NULL) {
            for(i = 0; i < json_object_array_length(results); i++) {
		        video = json_object_array_get_idx(results, i);
                titleObj = getObj_rec(video, TITLE_FIELD);

                if(titleObj != NULL) {
                    for(int i = 0; i < titlesRegex->length; i++) {
                        if(match_pattern((char *)json_object_get_string(titleObj), (titlesRegex->elements[i]).value)) {
                            save_video(video, json_object_get_string(titleObj));
                            break;
                        }
                    } 
                    
                }
	        }
        }
    }
    return 0;
}

int videopage_handler(YPage *page,STR_ARRAY *titlesRegex, char *url, char* parseFile) {
    struct json_object *json = NULL;

    if(url != NULL && titlesRegex != NULL) {
        //printf("VideoPage : %s\n", url);
        set_url(page, url);
        //print_page(page);
        downloadPage_and_replace(parseFile, page);
        file_tojson(parseFile, &json);
        //save_data(json, titlesRegex);
    }

    json_object_put(json);

    return 0;
}