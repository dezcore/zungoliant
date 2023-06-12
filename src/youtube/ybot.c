#include "../../include/youtube/ybot.h"

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

int run_ybot() {
    Element *url = NULL;
    struct json_object *json = NULL;
    Ybot *bot = malloc(sizeof(*bot));
    YPage *page = malloc(sizeof(*page));
    YPage *page1 =  malloc(sizeof(*page1));
    char *parseFile = NULL, *urlsFileSrc = NULL;
    const char* titles_regex = "/data/file/titles_regex";

    init_env();
    init_ybot(bot);
    init_yPage(page);
    init_yPage(page1);
    init_urls(&bot->urls_fifo, &urlsFileSrc);  

    get_pwd(&parseFile, PARSE_FILE_PATH);
    set_yPage(page, 0,  "", " ", (char*)titles_regex);
    set_yPage(page1, 1, "", " ", (char*)titles_regex);
    
    if(urlsFileSrc != NULL && page != NULL) {
        while(0 < bot->urls_fifo->size) {
            url = pop(bot->urls_fifo);
            if(url != NULL) {
                printf("Url : %s\n", url->value);
                if(match_pattern(url->value, ".+watch\\?v.*")) {//VIDEOPAGE
                    pages_handler(page, url->value, parseFile, bot->urls_fifo);
                } else if(match_pattern(url->value, "@.+")) {// Channel page
                    pages_handler(page1, url->value, parseFile, bot->urls_fifo);
                }
                //print_yfile(bot->data_fifo);
                //json_object_put(json);
                freeElement(url);
            }
            //break;
        }
    }
    
    free(parseFile);
    free(urlsFileSrc);
    free_yPage(page);
    free_yPage(page1);
    free_ybot(bot);
    return 0;
}

int init_ybot(Ybot *bot) {
    if(bot != NULL) {
        bot->urls_fifo = malloc(sizeof(*bot->urls_fifo));        
        bot->data_fifo = malloc(sizeof(*bot->data_fifo));

        init_yfile(bot->data_fifo);
        init_file_struct(bot->urls_fifo);
    }
    return 0;
}

int free_ybot(Ybot *bot) {
    if(bot != NULL) {
        freeFile(bot->urls_fifo);
        free_yfile(bot->data_fifo);
    }
    free(bot);
    return 0;
}