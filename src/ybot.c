#include "./../include/ybot.h"

int init_ybot(Ybot **bot) {
    *bot = malloc(sizeof(*bot));

    if(*bot != NULL) {
        (*bot)->urls_fifo = init();
        //init_yfile(&(*bot)->data_fifo);
    }

    return 0;
}

int free_ybot(Ybot *bot) {
    if(bot != NULL) {
        freeFile(bot->urls_fifo);
        //free_yfile(&bot->data_fifo);
        free(bot);
    }

    return 0;
}

int run_ybot() {
    Ybot *bot = NULL; 
    init_ybot(&bot);
    free_ybot(bot);
    return 0;
}