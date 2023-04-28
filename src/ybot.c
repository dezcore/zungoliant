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

int save_data(char* fileContent, Yfile **data_fifo) {
    unsigned int ii;
    struct json_object *json, *results;
    struct json_object *video, *titleObj, *videoObj, *imgObj;
    char *saveFilePath = getAbsolutePath("/data/file/test_json");

    if(fileContent != NULL && *data_fifo != NULL) {
        json = getJson(fileContent);

        if(json != NULL) {
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
    }
    free(saveFilePath);
    return 0;
}

int extract_pagedata(char *downloadPage, Yfile **data_fifo) {
    char *contents;
    char rpl[] = " ";
    char *parseContentPath = NULL; 
    char *patterns[] = {"var ytInitialData = ", ";"}; //"/.+=./"; , ";$"
    //char *saveFilePath = getAbsolutePath("/data/file/hello_regex");

    if(downloadPage != NULL) {
        parseYFile(downloadPage);
        contents = (char*) malloc(sizeof(char));        
        get_absolutePath(YINITDATA_FILE_PATH, &parseContentPath);
        if(parseContentPath != NULL) {
            contents = load_file(parseContentPath, contents);
            if(contents != NULL) {
                for(int i = 0; i < 2; i++) {
                    regex_replace(&contents, patterns[i], rpl);
                }
                //appendStrToFile(saveFilePath, contents);
                save_data(contents, &(*data_fifo));
                free(contents);
            }
            free(parseContentPath);
        }
    }

    //free(saveFilePath);
    return 0;
}

int init_urls(File **urls_fifo,  char **urlsFileSrc) {
    char *urlsFile =  NULL;

    get_absolutePath(URLS_FILE, &urlsFile);

    if(urlsFile != NULL) {
        fileToFifo(urlsFile, *urls_fifo);
        *urlsFileSrc = urlsFile;
    }

    return 0;
}

int run_ybot() {
    Ybot *bot = NULL;
    Element *url = NULL; 
    char *urlsFileSrc =  NULL;
    char *downloadPageSrc = NULL; 

    init_ybot(&bot);
    init_urls(&bot->urls_fifo, &urlsFileSrc);     
    get_absolutePath(DOWNLOAD_FILE, &downloadPageSrc);

    if(downloadPageSrc != NULL && urlsFileSrc != NULL) {
        while(0 < bot->urls_fifo->size) {
            url = pop(bot->urls_fifo);

            if(url != NULL) {
                downloadPage(url->value, downloadPageSrc);
                extract_pagedata(downloadPageSrc, &bot->data_fifo);
                print_yfile(bot->data_fifo);
                freeElement(url);
                url = NULL;
            }
        }

        free(urlsFileSrc);
        free(downloadPageSrc);
    }

    if(bot != NULL)
        free_ybot(bot);
    
    return 0;
}