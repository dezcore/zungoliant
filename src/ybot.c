#include "./../include/ybot.h"

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
        free(bot);
    }

    return 0;
}

int save_data(struct json_object *json, Yfile **data_fifo) {
    unsigned int ii;
    struct json_object *results;
    struct json_object *video, *titleObj, *videoObj, *imgObj;
    char *saveFilePath = getAbsolutePath("/data/file/test_json");

    if(json != NULL && *data_fifo != NULL) {
        results = getObj_rec(json, YRESULTS_FIELDS);

        if(results != NULL) {
            for(ii = 0; ii < json_object_array_length(results); ii++){
		        video = json_object_array_get_idx(results, ii);
                titleObj = getObj_rec(video, TITLE_FIELD);
                videoObj =  getObj_rec(video, VIDEOID_FIELD);
                imgObj = getObj_rec(video, IMG_FIELD);

                if(videoObj != NULL && titleObj != NULL && imgObj != NULL) {
                    push_ydata( &(*data_fifo), 
                    json_object_get_string(titleObj), 
                    json_object_get_string(imgObj), 
                    json_object_get_string(videoObj)); 
                }
	        }
        }
        json_object_put(json);
    }
    free(saveFilePath);
    return 0;
}

int init_urls(File **urls_fifo,  char **urlsFileSrc) {
    char *urlsFile =  NULL;

    get_pwd(&urlsFile, URLS_FILE);

    if(urlsFile != NULL) {
        fileToFifo(urlsFile, *urls_fifo);
        *urlsFileSrc = urlsFile;
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

        free(parseDir);
        free(regexDir);
        free(downloadDir);
    }

    return 0;
}

int run_ybot() {
    Ybot *bot = NULL;
    Element *url = NULL; 
    char* parseFile = NULL;
    char *urlsFileSrc =  NULL;
    YPage *page = malloc(sizeof(*page));

    init_env();
    init_ybot(&bot);
    init_urls(&bot->urls_fifo, &urlsFileSrc);
    get_pwd(&parseFile, PARSE_FILE_PATH);

    init_yPage(page, 0, "", " ");
    
    if(urlsFileSrc != NULL && page != NULL) {
        while(0 < bot->urls_fifo->size) {
            url = pop(bot->urls_fifo);
            if(url != NULL) {
                set_url(page, url->value);
                //print_page(page);
                downloadPage_and_replace(parseFile, page);
                //file_tojson(parseFile, &(page->json));
                //save_data(page->json, &bot->data_fifo);
                //print_yfile(bot->data_fifo);
                freeElement(url);
                url = NULL;
            }
        }

        free(parseFile);
        free(urlsFileSrc);
        free_yPage(page);
    }

    if(bot != NULL)
        free_ybot(bot);
    
    return 0;
}