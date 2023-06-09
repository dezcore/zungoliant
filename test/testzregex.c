#include "./../include/testzregex.h"
#define STR_SIZE 100

int test_downloadPage_and_replace() {
    Element *url = NULL; 
    char *urlsFileSrc =  NULL;
    char *downloadPageSrc = NULL;
    File *urls_fifo = malloc(sizeof(*urls_fifo)); 

    get_absolutePath(TEST_URLS_FILE, &urlsFileSrc);
    init_file_struct(urls_fifo);
    
    if(urlsFileSrc != NULL)
        fileToFifo(urlsFileSrc, urls_fifo);

    if(urls_fifo !=  NULL) {
        url = pop(urls_fifo);
        get_absolutePath(TEST_DOWNLOAD_FILE, &downloadPageSrc);

        if(downloadPageSrc != NULL && url != NULL) {
            downloadPage_bycontains(&url->value, downloadPageSrc, YINITDATA_VAR);
            //extract_htmlpagedata(downloadPageSrc);
            freeElement(url);
            free(downloadPageSrc);
        }
        
        free(urlsFileSrc);
        freeFile(urls_fifo);
    } 
    return 0;
}